#include "./BasePostEffectComponent.h"
#include "./Renderer/DirectXRenderManager.h"

namespace mslib {
namespace component {

void BasePostEffectComponent::Update() {
	
}

void BasePostEffectComponent::FixedUpdate() {
	render::PostEffectData posteffectData;
	render::DirectXRender::GetInstance().DrawPostEffect(posteffectData);
}

}
}

