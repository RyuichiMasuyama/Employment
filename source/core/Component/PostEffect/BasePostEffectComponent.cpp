#include "./BasePostEffectComponent.h"
#include "./Renderer/RenderTerget.h"

namespace mslib {
namespace component {

BasePostEffectComponent::BasePostEffectComponent(std::weak_ptr<render::RenderTerget> _renderTerget):
	m_renderTerget(_renderTerget){
	m_parameter = std::make_shared<render::PostEffect>();
	m_renderTerget.lock()->SetPostEffectData(m_parameter);
}

}
}

