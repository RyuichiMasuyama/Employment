#pragma once

#include "./core/Object/Object.h"
#include "./Renderer/PostEffect.h"

namespace mslib {
namespace render {
class RenderTerget;
}

namespace component {

class BasePostEffectComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	BasePostEffectComponent(std::weak_ptr<render::RenderTerget> _renderTerget);
	virtual ~BasePostEffectComponent() = default;

	void FixedUpdate()override;

	void SetPostEffectFlag(bool _flag, render::POSTEFFECT_TYPE _type);

	void SetGauusePower(float _power);
	void SetBloomPower(float _power);
private:
	float m_gauusePower;
	render::PostEffectStatus m_status;
	std::shared_ptr<render::PostEffect> m_parameter;
	// カメラからレンダーターゲットを受け取る
	std::weak_ptr<render::RenderTerget> m_renderTerget;
};

}
}