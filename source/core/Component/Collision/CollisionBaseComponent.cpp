#include "./CollisionBaseComponent.h"
namespace mslib {
namespace component {
CollisionBaseComponent::CollisionBaseComponent(collision::CollisionType _type) :m_collisionType(_type){

}

void CollisionBaseComponent::Initialize() {
	base::Initialize();
}


const collision::CollisionType & CollisionBaseComponent::GetCollisionType() {
	return m_collisionType;
}

const math::AABB & CollisionBaseComponent::GetAABB() {
	return  m_aabb;
}
}
}