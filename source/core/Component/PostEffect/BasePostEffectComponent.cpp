#include "./BasePostEffectComponent.h"
#include "./Renderer/RenderTerget.h"

namespace mslib {
namespace component {

BasePostEffectComponent::BasePostEffectComponent(std::weak_ptr<render::RenderTerget> _renderTerget) :
	m_renderTerget(_renderTerget) {
	m_parameter = std::make_shared<render::PostEffect>(_renderTerget.lock()->GetCameraTexture());
	m_renderTerget.lock()->SetPostEffectData(m_parameter);
}

void BasePostEffectComponent::FixedUpdate() {
	if (m_status.OnFlag[static_cast<unsigned int>(render::POSTEFFECT_TYPE::GAUSS)]) {
		float total = 0.0f;
		const int NUM_WEIGHT = 8;
		float mWeights[NUM_WEIGHT];
		for (int i = 0; i < NUM_WEIGHT; i++) {
			float pos = (float)i * 2.0f;
			mWeights[i] = expf(-pos * pos * m_gauusePower);
			total += mWeights[i];
		}

		// d‚Ý‚Ì‹KŠi‰»
		for (int i = 0; i < NUM_WEIGHT; i++)
			m_status.GaussPower[i] = mWeights[i] / total * 0.5f;

	}
	m_parameter->SetStatus(m_status);
}

void BasePostEffectComponent::SetPostEffectFlag(bool _flag, render::POSTEFFECT_TYPE _type) {
	m_status.OnFlag[static_cast<unsigned int>(render::POSTEFFECT_TYPE::GAUSS)] = _flag;
}

void BasePostEffectComponent::SetGauusePower(float _power) {
	m_gauusePower = _power;
}

void BasePostEffectComponent::SetBloomPower(float _power) {

}

}
}

