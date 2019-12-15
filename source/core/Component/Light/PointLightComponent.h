#pragma once

#include "./base/BaseLightComponent.h"

namespace mslib {
namespace component {

class PointLightComponent;
using PointLightComponentPtr = std::weak_ptr<PointLightComponent>;
using PointLightComponentSPtr = std::shared_ptr<PointLightComponent>;

class PointLightComponent final:public BaseLightComponent {
	BASE_CLASS_IS(BaseLightComponent)
public:
	PointLightComponent();
	virtual ~PointLightComponent() = default;

	void Initialize() override {};
	void FixedUpdate() override;

private:
};

}
}