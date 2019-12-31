#include "FeadComponent.h"

namespace mslib {
namespace component {
FeadComponent::FeadComponent(std::string _textureNmae) :m_fileName(_textureNmae) {

}

void FeadComponent::Initialize() {
	base::Initialize();
	auto gameObject = m_transform.lock()->m_gameObject;
	feadModel.Load("assets/Quad.fbx");
	feadModel.SetShader("shader/vs2d.fx", shader::ShaderType::VS);
	feadModel.SetShader("shader/psfead.fx", shader::ShaderType::PS);
	feadModel.SetTexture(m_fileName, 0);
	auto materialPtr = feadModel.GetMaterialVectorPtr();

	m_ambX = &materialPtr->at(0)->GetetMaterial()->ambient.x;

	auto modelRender=gameObject->AddComponent<ModelRenderComponent>(&feadModel);
	modelRender.lock()->AfterFlagOn();
	m_feadlevel = 1.f;
}
void FeadComponent::SetFeadLevel(float _level) {
	m_feadlevel = _level;
}
void FeadComponent::Update() {
	*m_ambX = m_feadlevel;
}
}
}

