#pragma once

#include "./BaseLightComponent.h"

namespace mslib {
namespace component {

class LightComponent;
using LightComponentPtr = std::weak_ptr<LightComponent>;
using LightComponentSPtr = std::shared_ptr<LightComponent>;

class LightComponent :public BaseLightComponent {
	BASE_CLASS_IS(LightComponent)
public:
	LightComponent() = default;
	virtual ~LightComponent() = default;

	virtual void Initialize() override {};
	virtual void Update() override {}

private:
};

}
}