#include "CollisionManager.h"
#include "./Component/Collision/CollisionSphereComponent.h"

namespace mslib {
namespace manager {
void CollisionManager::Update() {

	// 空間を割り当てる
	SpatialAllocation();
	// ReleseSpatialAllocation();

	// 空間ごとに当たり判定を取る
	//for (unsigned int i = 0; i < m_allSpaceNum; i++) {
	std::vector<component::CollisionBaseComponentSPtr> _colDinAryPtr;
	std::vector<component::CollisionBaseComponentSPtr> _colChildDinAryPtr;

	// 当たり判定リストを持ってくる
	GetCollisionList(0, &_colDinAryPtr, &_colChildDinAryPtr);

	// 絶対に偶数になるので割り切れる
	unsigned int collsionNum = static_cast<unsigned int>(_colDinAryPtr.size() / 2);
	for (int i = 0; i < collsionNum; i++) {
		// 衝突判定
		CollisionHit(_colDinAryPtr[i * 2], _colDinAryPtr[i * 2 + 1]);
	}

	// 空間の解放
	ReleseSpatialAllocation();
}

void CollisionManager::Initialize(
	unsigned int _divisionNum,
	math::Vector3 _min,
	math::Vector3 _max) {
	// 規定以上の空間分割数にできない
	if (DIVISION_NUM_MAX <= _divisionNum) {
		return;
	}
	
	// 各レベルでの空間数を算出
	m_pow[0] = 1;
	for (int i = 1; i < DIVISION_NUM_MAX + 1; i++) {
		m_pow[i] = m_pow[i - 1] * 8;	// マジックナンバー　8分木なので1親空間に8つ子空間がある
	}

	// 総空間分割数を割り出す
	m_allSpaceNum = (m_pow[_divisionNum + 1] - 1) / 7;
	m_spaceDinamicArray.resize(m_allSpaceNum);

	// new char;

	// 領域の登録
	m_rgnMin = _min;
	m_rgnMax = _max;
	m_wight = _max - _min;
	auto i = static_cast<float>(1 << _divisionNum);
	m_unit = m_wight / static_cast<float>(1 << _divisionNum);

	// 空間分割数登録
	m_divisionNum = _divisionNum;

	return;
}

void CollisionManager::AddCollsion(component::CollisionBaseComponentSPtr _cplPtr) {
	m_collsionAllDinamicArray.push_back(_cplPtr);
}

void CollisionManager::Register(component::CollisionBaseComponentSPtr _colPtr) {
	// モートン番号を生成
	auto elem = GetMortonNumber(_colPtr->GetAABB());
	// モートン番号が総空間分割数を超えていなければ
	if (elem < m_allSpaceNum) {
		CreateNewSpace(elem);
		m_spaceDinamicArray[elem]->Push(_colPtr);
	}
	// 登録
	// m_collsionAllDinamicArray.push_back(_colPtr);
}

void CollisionManager::SpatialAllocation() {
	// 再登録を行う
	for (auto&itr : m_collsionAllDinamicArray) {
		Register(itr);
	}
}

void CollisionManager::ReleseSpatialAllocation(){
	// 全ての登録を削除
	for (auto&itr : m_activeSpaceDinamicArray) {
		(*itr)->Reset();
		(*itr) = nullptr;
	}
	m_activeSpaceDinamicArray.clear();
}

unsigned int CollisionManager::GetMortonNumber(const math::AABB & _aabb)
{
	// 最小レベルにおける各軸位置を算出
	auto lt = GetMortonPointElem(_aabb.min);
	auto rb = GetMortonPointElem(_aabb.max);

	// 空間番号を引き算して
	// 最上位区切りから所属レベルを算出
	auto def = rb ^ lt;
	unsigned int HiLevel = 1;
	for (int i = 0; i < m_divisionNum; i++)
	{
		unsigned int  check = (def >> (i * 3)) & 0x7;
		if (check != 0)
			HiLevel = i + 1;
	}
	unsigned  int SpaceNum = rb >> (HiLevel * 3);
	unsigned  int AddNum = (m_pow[m_divisionNum - HiLevel] - 1) / 7;
	SpaceNum += AddNum;

	if (SpaceNum > m_allSpaceNum)
		return 0xffffffff;

	return SpaceNum;
}

// 範囲内のオブジェクトを0.f~1.fで置き換え
unsigned int CollisionManager::GetMortonPointElem(const math::Vector3 & _pos) {
	return GetMorton3DNumber(
		static_cast<unsigned char>((_pos.x - m_rgnMin.x) / m_unit.x),
		static_cast<unsigned char>((_pos.y - m_rgnMin.y) / m_unit.y),
		static_cast<unsigned char>((_pos.z - m_rgnMin.z) / m_unit.z));
}

// モートンの番号を受け取る
unsigned int CollisionManager::GetMorton3DNumber(
	unsigned char _x, 
	unsigned char _y, 
	unsigned char _z) {
	return GetMortonBitSpearateFor3D(_x) | 
		   GetMortonBitSpearateFor3D(_y) << 1 | 
		   GetMortonBitSpearateFor3D(_z) << 2;
}

// モートン番号の取得のbit処理
unsigned int CollisionManager::GetMortonBitSpearateFor3D(unsigned char _n) {
	unsigned int s = _n;
	s = (s | s << 8) & 0x0000f00f;
	s = (s | s << 4) & 0x000c30c3;
	s = (s | s << 2) & 0x00249249;
	return s;
}

//　コリジョンのリストを生成する
//int CollisionManager::GetAllCollisionList(std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr) {
//	return 0;
//}

// コリジョンリストを取得
//void CollisionManager::GetCollisionList(
//	unsigned int _elem, 
//	std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr,
//	std::vector<component::CollisionBaseComponentSPtr>* _colChildDinAryPtr) {
//	// 空間内のオブジェクト同士の衝突リスト作成
//	// 空間内のCollisionを取得
//	if (m_spaceDinamicArray[_elem] == nullptr)return;
//	auto & elemColDynamicArray = m_spaceDinamicArray[_elem]->GetCollisionDynamicArray();
//
//	// 取得したCollisonを追加
//	for (auto itr : elemColDynamicArray) _colDinAryPtr->push_back(itr);
//	// _colDinAryPtr->insert(_colDinAryPtr->end(), elemColDynamicArray.begin(), elemColDynamicArray.end());
//
//	unsigned int objNum = 0;
//	// 子空間の
//	SearchChildList(_elem, _colChildDinAryPtr);
//}

void CollisionManager::GetCollisionList(
	unsigned int _elem,
	std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr,
	std::vector<component::CollisionBaseComponentSPtr>* _colChildDinAryPtr) {

	// 範囲外アクセスをしないようにする
	if (m_allSpaceNum < _elem) return;
	
	// ノードが形成されているか
	if (m_spaceDinamicArray[_elem] == nullptr) return;

	// ノード内の衝突Componentリストを取得
	auto collisionArray = m_spaceDinamicArray[_elem]->GetCollisionDynamicArray();
	unsigned int arraySize = static_cast<unsigned int>(collisionArray.size());
	for (int i = 0; i < arraySize; i++) {
		for (int j = i + 1; j < arraySize; j++) {
			_colDinAryPtr->push_back(collisionArray[i]);
			_colDinAryPtr->push_back(collisionArray[j]);
		}
		for (auto& itr : *_colChildDinAryPtr) {
			_colDinAryPtr->push_back(collisionArray[i]);
			_colDinAryPtr->push_back(itr);
		}
	}

	unsigned int nextElem;
	unsigned int objectNum = 0;
	bool flag = false;

	// 子空間に移動
	for (int i = 0; i < 8; i++) {
		nextElem = _elem * 8 + 1 + i;
		if (nextElem < m_allSpaceNum&&m_spaceDinamicArray[nextElem] != nullptr) {
			if (!flag) {
				for (auto& itr : collisionArray) {
					_colChildDinAryPtr->push_back(itr);
				objectNum++;
				}
			}
		}
		flag = true;
		GetCollisionList(nextElem, _colDinAryPtr, _colChildDinAryPtr);	// 子空間へ　
	}

	// スタックからオブジェクトを外す
	if (flag) {
		for (int i = 0; i < objectNum; i++) {
			_colChildDinAryPtr->pop_back();
		}
	}
	// collisionArray.clear();
	return;
}

std::vector<component::CollisionBaseComponentSPtr> CollisionManager::CreateCollisionList() {
	std::vector<component::CollisionBaseComponentSPtr> colComPtrDinamicArray;
	std::vector<component::CollisionBaseComponentSPtr> stackDinamcArray;

	if (m_spaceDinamicArray[0] == nullptr)return colComPtrDinamicArray;

	GetCollisionList(0, &colComPtrDinamicArray, &stackDinamcArray);

	return colComPtrDinamicArray;
}

void CollisionManager::SearchChildList(
	const unsigned int &_elem, 
	std::vector<component::CollisionBaseComponentSPtr>* _colChildDinAryPtr) {

	unsigned int objNum = 0;
	unsigned int nextElem;
	if (m_spaceDinamicArray[_elem] == nullptr) {
		return;
	}

	auto & elemColDynamicArray = m_spaceDinamicArray[_elem]->GetCollisionDynamicArray();
	for(auto itr: elemColDynamicArray) _colChildDinAryPtr->push_back(itr);

	// 子空間に移動
	for (int i = 0; i < 8; i++) {
		if (m_spaceDinamicArray[_elem]->GetCollisionDynamicArray().size() == 0)break;
		nextElem = _elem * 8 + 1 + i;
		if (nextElem < m_allSpaceNum) {
			SearchChildList(nextElem, _colChildDinAryPtr);	// 子空間へ
		}
	}
}

void CollisionManager::CollisionHit(
	component::CollisionBaseComponentSPtr _static, 
	component::CollisionBaseComponentSPtr _dynamic) {
	// AABBで前取り
	bool hit = false;
	if (_static->GetAABB().min.x<_dynamic->GetAABB().max.x && _dynamic->GetAABB().min.x<_static->GetAABB().max.x) {
		if (_static->GetAABB().min.y<_dynamic->GetAABB().max.y && _dynamic->GetAABB().min.y<_static->GetAABB().max.y) {
			if (_static->GetAABB().min.z<_dynamic->GetAABB().max.z && _dynamic->GetAABB().min.z<_static->GetAABB().max.z) {
				hit = true;
			}
		}
	}
	if (!hit)return;
	switch (_static->GetCollisionType())
	{
	case collision::CollisionType::Sphere:
		switch (_dynamic->GetCollisionType())
		{
		case collision::CollisionType::Sphere:
			// 球同士の当たり判定
			SphereToSphere(_static, _dynamic);
			break;
		case collision::CollisionType::Mesh:
			// 球メッシュの当たり判定
			break;
		default:
			break;
		}
		break;
	case collision::CollisionType::Mesh:
		break;
	default:
		break;
	}

}

void CollisionManager::SphereToSphere(
	component::CollisionBaseComponentSPtr _static,
	component::CollisionBaseComponentSPtr _dynamic) {


	// 当たり判定をキャスト
	component::CollisionSphereComponentSPtr spStatic, spDynamic;
	// 型はCollisionTypeで保障されているのでstatic_castで十分
	spStatic = std::static_pointer_cast<component::CollisionSphereComponent>(_static);
	spDynamic = std::static_pointer_cast<component::CollisionSphereComponent>(_dynamic);

	// サイズ
	float staticSize = spStatic->GetSize();
	float dynamicSize = spDynamic->GetSize();

	// 二点の位置
	math::Vector3 staticPos= spStatic->GetAABB().center;
	math::Vector3 dynamicPos = spDynamic->GetAABB().center;

	float interval = math::Vector3::Interval(staticPos, dynamicPos);
	float spSize = staticSize + dynamicSize;

	// 当たった
	if (interval <= spSize) {
		_static->GetTransform().lock()->m_gameObject->HitTriggerStay();
		_dynamic->GetTransform().lock()->m_gameObject->HitTriggerStay();
	}
}

void CollisionManager::CreateNewSpace(unsigned int _elem) {
	// 引数の要素番号
	while (m_spaceDinamicArray[_elem] == nullptr) {
		// 指定の要素番号に空間を新規作成
		m_spaceDinamicArray[_elem] = std::make_unique<collision::CollisionSpace>();

		// 初期化に必要なので追加
		m_activeSpaceDinamicArray.push_back(&m_spaceDinamicArray[_elem]);
		
		// 親空間にジャンプ
		_elem = (_elem - 1) >> 3;
		if (_elem >= m_allSpaceNum) break;
	}
	return;
}

}
namespace collision {
void CollisionSpace::Push(component::CollisionBaseComponentSPtr _com) {
	m_collsionDinamicArray.push_back(_com);
}
void CollisionSpace::Reset() {
	m_collsionDinamicArray.clear();
}
const std::vector<component::CollisionBaseComponentSPtr>& CollisionSpace::GetCollisionDynamicArray() {
	return m_collsionDinamicArray;
}

}
}
