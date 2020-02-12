#include "./PlayerCommandModelGameObject.h"
#include "./core/Component/Render/ModelRenderComponent.h"

namespace mslib {
namespace origin {
namespace game {

PlayerCommandModelGameObject::PlayerCommandModelGameObject(std::string _textureName) {
	m_texutreName = _textureName;
}

void PlayerCommandModelGameObject::Initialize() {
	base::Initialize();

	m_modelData.Load("assets/Quad.fbx");
	m_modelData.SetVertexShader("shader/testvs.fx");
	m_modelData.SetPixelShader("shader/ps2d.fx");
	m_modelData.SetTexture(m_texutreName, 0);

	AddComponent<component::ModelRenderComponent>(&m_modelData);

	m_position.y += 10.f;
}

}  // namespace game
}  // namespace origne
}  // namespace mslib