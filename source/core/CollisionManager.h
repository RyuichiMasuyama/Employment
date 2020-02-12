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

// ��ԕ��������˂�����
// �������ɂ����
class CollisionManager :public pattern::Singleton<CollisionManager>{
public:
	static constexpr unsigned int DIVISION_NUM_MAX = 8;

	void Update();
	
	// �������@
	// ����1:��ԕ�����
	// ����2:��Ԃ̃T�C�Y(min)
	// ����3:��Ԃ̃T�C�Y(max)
	void Initialize(unsigned int _divisionNum, math::Vector3 _min, math::Vector3 _max);

	void AddCollsion(component::CollisionBaseComponentSPtr _cplPtr);

	// �����蔻��N���X�̓o�^
	void Register(component::CollisionBaseComponentSPtr _colPtr);
	void Unregister(component::CollisionBaseComponentSPtr _colPtr);
	~CollisionManager() {
		m_collsionAllDinamicArray.clear();
	}
private:
	// ��Ԃ̊��蓖��
	void SpatialAllocation();
	// ��Ԃ̉��
	void ReleseSpatialAllocation();
	// ���W�����Ԕz��ԍ��Z�o����֐��Q(���[�g���Ȃ񂿂��)
	// �܂�؂��Q��
	unsigned int GetMortonNumber(const math::AABB& _aabb);
	unsigned int GetMortonPointElem(const math::Vector3& _pos);
	unsigned int GetMorton3DNumber(unsigned char _x, unsigned char _y, unsigned char _z);
	unsigned int GetMortonBitSpearateFor3D(unsigned char _n);

	// int GetAllCollisionList(std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr);

	// �Փ˔��胊�X�g�쐬�֐�
	void GetCollisionList(
		unsigned int _elem,
		std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr,
		std::vector<component::CollisionBaseComponentSPtr>* _colChildDinAryPtr
	);

	//void GetCollisionList(
		//unsigned int _elem,
		//std::vector<component::CollisionBaseComponentSPtr>* _colDinAryPtr,
		//std::vector<component::CollisionBaseComponentSPtr>* _colChildDinAryPtr);

	// �Փ˃��X�g�̍쐬
	std::vector<component::CollisionBaseComponentSPtr> CreateCollisionList();

	// ���w��Ԃ̏Փ˔��胊�X�g�������Ă���
	void SearchChildList(const unsigned int& _elem, std::vector<component::CollisionBaseComponentSPtr>* _colChildDinAryPtr);

	// �R���W�����̃q�b�g
	void CollisionHit(component::CollisionBaseComponentSPtr _static, component::CollisionBaseComponentSPtr _dynamic);

	// �e��̓����蔻��
	// CollisionHit�����Ŏg�p
	void SphereToSphere(component::CollisionBaseComponentSPtr _static, component::CollisionBaseComponentSPtr _dynamic);

	// �ȉ�������
	void SphereToMesh(component::CollisionBaseComponentSPtr _static, component::CollisionBaseComponentSPtr _dynamic);
	void MeshToSphere(component::CollisionBaseComponentSPtr _static, component::CollisionBaseComponentSPtr _dynamic);

	// ��Ԑ���
	void CreateNewSpace(unsigned int _elem);

	// ��ԕ�����
	int m_divisionNum;

	// ����Ԑ�(divisonNum�ɂ���ĕύX�����)
	unsigned int m_allSpaceNum;

	math::Vector3 m_rgnMin;	// �̈�̍ŏ��l
	math::Vector3 m_rgnMax;	// �̈�̍ő�l
	math::Vector3 m_wight;	// �̈�̕�
	math::Vector3 m_unit;	// �ŏ��̈�̕ӂ̒���

	std::array<unsigned int, DIVISION_NUM_MAX + 1> m_pow;	// �ׂ��搔�l�z��

	// �I�u�W�F�N�g
	std::vector<component::CollisionBaseComponentSPtr> m_collsionAllDinamicArray;
	// ��ԃN���X
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
// ��ԕ����Ɏg�����ԃN���X
class CollisionSpace {
public:
	CollisionSpace() = default;
	~CollisionSpace() { m_collsionDinamicArray.clear(); };
	void Push(component::CollisionBaseComponentSPtr _com);
	void Reset();
	const std::vector<component::CollisionBaseComponentSPtr>& GetCollisionDynamicArray();
private:
	// �I�u�W�F�N�g
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