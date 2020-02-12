#include "./RigidbodyComponent.h"
#include <./core/FpsManager.h>

namespace mslib {
namespace component {
math::Vector3 RigidbodyComponent::Acceleration = { 0.f, -9.8f, 0.f };

void RigidbodyComponent::Initialize() {
	base::Initialize();

	m_velocity = math::Vector3();
}

void RigidbodyComponent::Update() {
	float deltaTime= FpsManager::GetInstance().GetDeltaTime();

	m_velocity += Acceleration * deltaTime;
}

void RigidbodyComponent::FixedUpdate() {
	m_transform.lock()->m_position += m_velocity * 60.f / 1000.f;
}

}
}