#pragma once

#include "./base/BaseCameraComponent.h"

namespace mslib {
namespace component {
class CameraComponent: public BaseCameraComponent {
	BASE_CLASS_IS(BaseCameraComponent)
public:
	CameraComponent();
	virtual ~CameraComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void FixedUpdate() {}
};
}
}