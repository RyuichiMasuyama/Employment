#pragma once

#include "./core/Object/Object.h"

namespace mslib {
namespace component {

class RigidbodyComponent final :public Component {
	BASE_CLASS_IS(Component)
private:
	static math::Vector3 Acceleration;
public:
	RigidbodyComponent() = default;
	virtual ~RigidbodyComponent() = default;

	void Initialize()override;

	void Update()override;
	void FixedUpdate()override;
public:
	// ‰Á‘¬“x
	math::Vector3 m_velocity;
};

}
}