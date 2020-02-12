#include "CollisionManager.h"
#include "./Component/Collision/CollisionSphereComponent.h"

namespace mslib {
namespace manager {
void CollisionManager::Update() {

	// ��Ԃ����蓖�Ă�
	SpatialAllocation();
	// ReleseSpatialAllocation();

	// ��Ԃ��Ƃɓ����蔻������
	//for (unsigned int i = 0; i < m_allSpaceNum; i++) {
	std::vector<component::CollisionBaseComponentSPtr> _colDinAryPtr;
	std::vector<component::CollisionBaseComponentSPtr> _colChildDinAryPtr;

	// �����蔻�胊�X�g�������Ă���
	GetCollisionList(0, &_colDinAryPtr, &_colChildDinAryPtr);

	// ��΂ɋ����ɂȂ�̂Ŋ���؂��
	unsigned int collsionNum = static_cast<unsigned int>(_colDinAryPtr.size() / 2);
	for (int i = 0; i < collsionNum; i++) {
		// �Փ˔���
		CollisionHit(_colDinAryPtr[i * 2], _colDinAryPtr[i * 2 + 1]);
	}

	// ��Ԃ̉��
	ReleseSpatialAllocation();
}

void CollisionManager::Initialize(
	unsigned int _divisionNum,
	math::Vector3 _min,
	math::Vector3 _max) {
	// �K��ȏ�̋�ԕ������ɂł��Ȃ�
	if (DIVISION_NUM_MAX <= _divisionNum) {
		return;
	}
	
	// �e���x���ł̋�Ԑ����Z�o
	m_pow[0] = 1;
	for (int i = 1; i < DIVISION_NUM_MAX + 1; i++) {
		m_pow[i] = m_pow[i - 1] * 8;	// �}�W�b�N�i���o�[�@8���؂Ȃ̂�1�e��Ԃ�8�q��Ԃ�����
	}

	// ����ԕ�����������o��
	m_allSpaceNum = (m_pow[_divisionNum + 1] - 1) / 7;
	m_spaceDinamicArray.resize(m_allSpaceNum);

	// new char;

	// �̈�̓o�^
	m_rgnMin = _min;
	m_rgnMax = _max;
	m_wight = _max - _min;
	auto i = static_cast<float>(1 << _divisionNum);
	m_unit = m_wight / static_cast<float>(1 << _divisionNum);

	// ��ԕ������o�^
	m_divisionNum = _divisionNum;

	return;
}

void CollisionManager::AddCollsion(component::CollisionBaseComponentSPtr _cplPtr) {
	m_collsionAllDinamicArray.push_back(_cplPtr);
}

void CollisionManager::Register(component::CollisionBaseComponentSPtr _colPtr) {
	// ���[�g���ԍ��𐶐�
	auto elem = GetMortonNumber(_colPtr->GetAABB());
	// ���[�g���ԍ�������ԕ������𒴂��Ă��Ȃ����
	if (elem < m_allSpaceNum) {
		CreateNewSpace(elem);
		m_spaceDinamicArray[elem]->Push(_colPtr);
	}
	// �o�^
	// m_collsionAllDinamicArray.push_back(_colPtr);
}

void CollisionManager::SpatialAllocation() {
	// �ēo�^���s��
	for (auto&itr : m_collsionAllDinamicArray) {
		Register(itr);
	}
}

void CollisionManager::ReleseSpatialAllocation(){
	// �S�Ă̓o�^���폜
	for (auto&itr : m_activeSpaceDinamicArray) {
		(*itr)->Reset();
		(*itr) = nullptr;
	}
	m_activeSpaceDinamicArray.clear();
}

unsigned int CollisionManager::GetMortonNumber(const math::AABB & _aabb)
{
	// �ŏ����x���ɂ�����e���ʒu���Z�o
	auto lt = GetMortonPointElem(_aabb.min);
	auto rb = GetMortonPointElem(_aabb.max);

	// ��Ԕԍ��������Z����
	// �ŏ�ʋ�؂肩�珊�����x�����Z�o
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

// �͈͓��̃I�u�W�F�N�g��0.f~1.f�Œu������
unsigned int CollisionManager::GetMortonPointElem(const math::Vector3 & _pos) {
	return GetMorton3DNumber(
		static_cast<unsigned char>((_pos.x - m_rgnMin.x) / m_unit.x),
		static_cast<unsigned char>((_pos.y - m_rgnMin.y) / m_unit.y),
		static_cast<unsigned char>((_pos.z - m_rgnMin.z) / m_unit.z));
}

// ���[�g���̔ԍ����󂯎��
unsigned int CollisionManager::GetMorton3DNumber(
	unsigned char _x, 
	unsigned char _y, 
	unsigned char _z) {
	return GetMortonBitSpearateFor3D(_x) | 
		   GetMortonBitSpearateFor3D(_y) << 1 | 
		   GetMortonBitSpearateFor3D(_z) << 2;
}

// ���[�g���ԍ��̎擾��bit����
unsigned int CollisionManager::GetMortonBitSpearateFor3D(unsigned char _n) {
	unsigned int s = _n;
	s = (s | s << 8) & 0x0000f00f;
	s = (s | s << 4) & 0x000c30c3;
	s = (s | s << 2) & 0x00249249;
	return s;
}

//�@�R���W�����̃��X�g�𐶐�����
//int CollisionManager::GetAllCollisionList(std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr) {
//	return 0;
//}

// �R���W�������X�g���擾
//void CollisionManager::GetCollisionList(
//	unsigned int _elem, 
//	std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr,
//	std::vector<component::CollisionBaseComponentSPtr>* _colChildDinAryPtr) {
//	// ��ԓ��̃I�u�W�F�N�g���m�̏Փ˃��X�g�쐬
//	// ��ԓ���Collision���擾
//	if (m_spaceDinamicArray[_elem] == nullptr)return;
//	auto & elemColDynamicArray = m_spaceDinamicArray[_elem]->GetCollisionDynamicArray();
//
//	// �擾����Collison��ǉ�
//	for (auto itr : elemColDynamicArray) _colDinAryPtr->push_back(itr);
//	// _colDinAryPtr->insert(_colDinAryPtr->end(), elemColDynamicArray.begin(), elemColDynamicArray.end());
//
//	unsigned int objNum = 0;
//	// �q��Ԃ�
//	SearchChildList(_elem, _colChildDinAryPtr);
//}

void CollisionManager::GetCollisionList(
	unsigned int _elem,
	std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr,
	std::vector<component::CollisionBaseComponentSPtr>* _colChildDinAryPtr) {

	// �͈͊O�A�N�Z�X�����Ȃ��悤�ɂ���
	if (m_allSpaceNum < _elem) return;
	
	// �m�[�h���`������Ă��邩
	if (m_spaceDinamicArray[_elem] == nullptr) return;

	// �m�[�h���̏Փ�Component���X�g���擾
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

	// �q��ԂɈړ�
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
		GetCollisionList(nextElem, _colDinAryPtr, _colChildDinAryPtr);	// �q��Ԃց@
	}

	// �X�^�b�N����I�u�W�F�N�g���O��
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

	// �q��ԂɈړ�
	for (int i = 0; i < 8; i++) {
		if (m_spaceDinamicArray[_elem]->GetCollisionDynamicArray().size() == 0)break;
		nextElem = _elem * 8 + 1 + i;
		if (nextElem < m_allSpaceNum) {
			SearchChildList(nextElem, _colChildDinAryPtr);	// �q��Ԃ�
		}
	}
}

void CollisionManager::CollisionHit(
	component::CollisionBaseComponentSPtr _static, 
	component::CollisionBaseComponentSPtr _dynamic) {
	// AABB�őO���
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
			// �����m�̓����蔻��
			SphereToSphere(_static, _dynamic);
			break;
		case collision::CollisionType::Mesh:
			// �����b�V���̓����蔻��
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


	// �����蔻����L���X�g
	component::CollisionSphereComponentSPtr spStatic, spDynamic;
	// �^��CollisionType�ŕۏႳ��Ă���̂�static_cast�ŏ\��
	spStatic = std::static_pointer_cast<component::CollisionSphereComponent>(_static);
	spDynamic = std::static_pointer_cast<component::CollisionSphereComponent>(_dynamic);

	// �T�C�Y
	float staticSize = spStatic->GetSize();
	float dynamicSize = spDynamic->GetSize();

	// ��_�̈ʒu
	math::Vector3 staticPos= spStatic->GetAABB().center;
	math::Vector3 dynamicPos = spDynamic->GetAABB().center;

	float interval = math::Vector3::Interval(staticPos, dynamicPos);
	float spSize = staticSize + dynamicSize;

	// ��������
	if (interval <= spSize) {
		_static->GetTransform().lock()->m_gameObject->HitTriggerStay();
		_dynamic->GetTransform().lock()->m_gameObject->HitTriggerStay();
	}
}

void CollisionManager::CreateNewSpace(unsigned int _elem) {
	// �����̗v�f�ԍ�
	while (m_spaceDinamicArray[_elem] == nullptr) {
		// �w��̗v�f�ԍ��ɋ�Ԃ�V�K�쐬
		m_spaceDinamicArray[_elem] = std::make_unique<collision::CollisionSpace>();

		// �������ɕK�v�Ȃ̂Œǉ�
		m_activeSpaceDinamicArray.push_back(&m_spaceDinamicArray[_elem]);
		
		// �e��ԂɃW�����v
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
