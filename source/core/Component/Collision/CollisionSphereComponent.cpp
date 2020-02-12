#include "./CollisionSphereComponent.h"
#include <./core/CollisionManager.h>

namespace mslib {
namespace component {

CollisionSphereComponent::CollisionSphereComponent() :CollisionBaseComponent(collision::CollisionType::Sphere) {
}

void CollisionSphereComponent::Initialize() {
	base::Initialize();

	// �����l
	m_size = 1.f;
	// aabb�̃Z�b�g
	m_aabb.SetAABB(math::Vector3(m_size, m_size, m_size), m_transform.lock()->m_position);

	manager::CollisionManager::GetInstance().AddCollsion(shared_from_this());
}

void CollisionSphereComponent::Update() {
	// aabb�̃Z�b�g
	m_aabb.SetAABB(math::Vector3(m_size, m_size, m_size), m_transform.lock()->m_position);
}

const float & CollisionSphereComponent::GetSize() {
	return m_size;
}

void CollisionSphereComponent::SetSize(float _size) {
	m_size = _size;
}

}
}