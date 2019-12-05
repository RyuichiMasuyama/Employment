#pragma once

#include "./base/BaseLightComponent.h"

namespace mslib {
namespace component {

class SpotLightComponent;
using SpotLightComponentPtr = std::weak_ptr<SpotLightComponent>;
using SpotLightComponentSPtr = std::shared_ptr<SpotLightComponent>;

class SpotLightComponent final:public BaseLightComponent {
	BASE_CLASS_IS(BaseLightComponent)
public:
	SpotLightComponent();
	virtual ~SpotLightComponent() = default;

	virtual void Initialize() override {};
	void FixedUpdate() override;

private:
};

}
}