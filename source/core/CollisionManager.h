#pragma once

#include <Singleton.h>
#include <vector>
#include <array>
#include "../Math/Vector.h"
#include <DirectX/math/AABB.h>

#define COLLISION_THREE_SIZE_MAX math::Vector3(1000.f, 1000.f, 1000.f)
#define COLLISION_THREE_SIZE_MIN math::Vector3(0.f, 0.f, 0.f)

namespace mslib {
namespace component {
class CollisionBaseComponent;
using CollisionBaseComponentPtr = std::weak_ptr<CollisionBaseComponent>;
using CollisionBaseComponentSPtr = std::shared_ptr<CollisionBaseComponent>;
}
namespace collision {
class CollisionSpace;
using CollisionSpacePtr = std::weak_ptr<CollisionSpace>;
using CollisionSpaceSPtr= std::shared_ptr<CollisionSpace>;
using CollisionSpaceUPtr = std::unique_ptr<CollisionSpace>;

class CollisionObject;
using CollisionObjectPtr = std::weak_ptr<CollisionObject>;
using CollisionObjectSPtr = std::shared_ptr<CollisionObject>;
using CollisionObjectUPtr = std::unique_ptr<CollisionObject>;
}

namespace manager {

class Tree;
using TreePtr = std::weak_ptr<Tree>;
using TreeSPtr = std::shared_ptr<Tree>;

// 空間分割を兼ねた処理
// 分割数によって
class CollisionManager :public pattern::Singleton<CollisionManager>{
public:
	static constexpr unsigned int DIVISION_NUM_MAX = 8;

	void Update();
	
	// 初期化　
	// 引数1:空間分割数
	// 引数2:空間のサイズ(min)
	// 引数3:空間のサイズ(max)
	void Initialize(unsigned int _divisionNum, math::Vector3 _min, math::Vector3 _max);

	void AddCollsion(component::CollisionBaseComponentSPtr _cplPtr);

	// 当たり判定クラスの登録
	void Register(component::CollisionBaseComponentSPtr _colPtr);
	void Unregister(component::CollisionBaseComponentSPtr _colPtr);
	~CollisionManager() {
		m_collsionAllDinamicArray.clear();
	}
private:
	// 空間の割り当て
	void SpatialAllocation();
	// 空間の解放
	void ReleseSpatialAllocation();
	// 座標から空間配列番号算出する関数群(モートンなんちゃら)
	// まるぺけ参照
	unsigned int GetMortonNumber(const math::AABB& _aabb);
	unsigned int GetMortonPointElem(const math::Vector3& _pos);
	unsigned int GetMorton3DNumber(unsigned char _x, unsigned char _y, unsigned char _z);
	unsigned int GetMortonBitSpearateFor3D(unsigned char _n);

	// int GetAllCollisionList(std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr);

	// 衝突判定リスト作成関数
	void GetCollisionList(
		unsigned int _elem,
		std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr,
		std::vector<component::CollisionBaseComponentSPtr>* _colChildDinAryPtr
	);

	//void GetCollisionList(
		//unsigned int _elem,
		//std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr,
		//std::vector<component::CollisionBaseComponentSPtr>* _colChildDinAryPtr);

	// 衝突リストの作成
	std::vector<component::CollisionBaseComponentSPtr> CreateCollisionList();

	// 下層空間の衝突判定リストを持ってくる
	void SearchChildList(const unsigned int& _elem, std::vector<component::CollisionBaseComponentSPtr>* _colChildDinAryPtr);

	// コリジョンのヒット
	void CollisionHit(component::CollisionBaseComponentSPtr _static, component::CollisionBaseComponentSPtr _dynamic);

	// 各種の当たり判定
	// CollisionHit内部で使用
	void SphereToSphere(component::CollisionBaseComponentSPtr _static, component::CollisionBaseComponentSPtr _dynamic);

	// 以下未実装
	void SphereToMesh(component::CollisionBaseComponentSPtr _static, component::CollisionBaseComponentSPtr _dynamic);
	void MeshToSphere(component::CollisionBaseComponentSPtr _static, component::CollisionBaseComponentSPtr _dynamic);

	// 空間生成
	void CreateNewSpace(unsigned int _elem);

	// 空間分割数
	int m_divisionNum;

	// 総空間数(divisonNumによって変更される)
	unsigned int m_allSpaceNum;

	math::Vector3 m_rgnMin;	// 領域の最小値
	math::Vector3 m_rgnMax;	// 領域の最大値
	math::Vector3 m_wight;	// 領域の幅
	math::Vector3 m_unit;	// 最小領域の辺の長さ

	std::array<unsigned int, DIVISION_NUM_MAX + 1> m_pow;	// べき乗数値配列

	// オブジェクト
	std::vector<component::CollisionBaseComponentSPtr> m_collsionAllDinamicArray;
	// 空間クラス
	std::vector<collision::CollisionSpaceUPtr> m_spaceDinamicArray;
	std::vector<collision::CollisionSpaceUPtr*> m_activeSpaceDinamicArray;
}; 

class Tree :public std::enable_shared_from_this<Tree> {
private:
	std::shared_ptr<Tree>  m_parent;
	std::array<std::shared_ptr<Tree>, 8> m_chile;
public:
	std::shared_ptr<Tree> GetFront() { return m_parent; }
	std::shared_ptr<Tree> GetBack(int i) { if (i < 8 && 0 <= i)return m_chile[i]; }

};

}
namespace collision {
// 空間分割に使われる空間クラス
class CollisionSpace {
public:
	CollisionSpace() = default;
	~CollisionSpace() { m_collsionDinamicArray.clear(); };
	void Push(component::CollisionBaseComponentSPtr _com);
	void Reset();
	const std::vector<component::CollisionBaseComponentSPtr>& GetCollisionDynamicArray();
private:
	// オブジェクト
	std::vector<component::CollisionBaseComponentSPtr> m_collsionDinamicArray;
};

class CollisionObject {
public:
	CollisionObject() = default;
	~CollisionObject() = default;

private:
	component::CollisionBaseComponentSPtr m_collision;
};
}
}