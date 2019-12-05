#pragma once

#include "./base/BaseCameraComponent.h"

namespace mslib {
namespace component {
class ShadowMapCameraComponent : public BaseCameraComponent {
	BASE_CLASS_IS(BaseCameraComponent)
public:
	ShadowMapCameraComponent();
	virtual ~ShadowMapCameraComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void FixedUpdate() {}

};
}
}