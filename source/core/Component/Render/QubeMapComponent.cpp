#include "QubeMapComponent.h"

namespace mslib {
namespace component {
QubeMapComponent::QubeMapComponent(std::string _mapTextureName):
	m_mapTextureName(_mapTextureName){

}

void QubeMapComponent::Initialize() {
	base::Initialize();

	m_modelData.Load("assets/QubeMap.fbx");
	m_modelData.SetVertexShader("shader/testvs.fx");
	m_modelData.SetPixelShader("shader/ps2d.fx");
	m_modelData.SetTexture(m_mapTextureName, 0);

	m_transform.lock()->m_gameObject->AddComponent<ModelRenderComponent>(&m_modelData);
	m_transform.lock()->m_rotate = math::Vector3(0,90,90);
	m_transform.lock()->m_scale *= math::Vector3(3000.f, 3000.f, 3000.f);
}
}  // namespace component
}  // namespace mslib