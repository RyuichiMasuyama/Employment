#pragma once

#include <./core/Object/object.h>
#include <DirectX/math/AABB.h>

namespace mslib {
namespace collision {
enum class CollisionType {
	Sphere,
	Mesh
};
}
namespace component {


class CollisionBaseComponent;
using CollisionBaseComponentPtr = std::weak_ptr<CollisionBaseComponent>;
using CollisionBaseComponentSPtr = std::shared_ptr<CollisionBaseComponent>;

class CollisionBaseComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	CollisionBaseComponent(collision::CollisionType);
	~CollisionBaseComponent() = default;

	// èâä˙âª
	void Initialize()override;

	const collision::CollisionType& GetCollisionType();
	const math::AABB& GetAABB();
protected:
	const collision::CollisionType m_collisionType;
	math::AABB m_aabb;
};
}
}