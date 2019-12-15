#pragma once

#include "./base/BaseLightComponent.h"

namespace mslib {
namespace component {

class DirectionalLightComponent;
using DirectionalLightComponentPtr = std::weak_ptr<DirectionalLightComponent>;
using DirectionalLightComponentSPtr = std::shared_ptr<DirectionalLightComponent>;

class DirectionalLightComponent final:public BaseLightComponent {
	BASE_CLASS_IS(BaseLightComponent)
public:
	DirectionalLightComponent();
	virtual ~DirectionalLightComponent() = default;

	virtual void Initialize() override {};
	virtual void FixedUpdate() override;
private:

};

}
}