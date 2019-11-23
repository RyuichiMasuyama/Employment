#pragma once

#include "./core/Object/Object.h"

namespace mslib {
namespace component {

class BasePostEffectComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	BasePostEffectComponent() = default;
	virtual ~BasePostEffectComponent() = default;

	virtual void Initialize() {}
	virtual void Update() override;
	virtual void FixedUpdate() override;

private:
	// Gaussエフェクトの力
	float m_gaussPower;


};

}
}