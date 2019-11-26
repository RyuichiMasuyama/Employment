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

	std::weak_ptr<render::PostEffect> GetParamater() { return m_parameter; }
private:
	std::shared_ptr<render::PostEffect> m_parameter;
	// カメラからレンダーターゲットを受け取る
	std::weak_ptr<render::RenderTerget> m_renderTerget;
};

}
}