#include "./GameObjectGround.h"
#include "./ImGui/imgui.h"
#include "./core/Component/Render/ModelRenderComponent.h"
#include "./AssetManager/MeshLoader.h"
#include "./Renderer/Model.h"

#include "./AssetManager/TextureLoader.h"
namespace mslib {
namespace origin {

void GameObjectGround::Initialize() {
	base::Initialize();

	m_modelData.Load("assets/box.fbx");
	m_modelData.SetVertexShader("shader/testvs.fx");
	m_modelData.SetPixelShader("shader/ps2d.fx");
	m_modelData.SetTexture("Dragon_Bump_Col2.jpg", 0);

	loader::MeshLoader load;
	loader::TextureLoader textureLoader;
	auto renderComponent = AddComponent<component::ModelRenderComponent>(&m_modelData);
	// renderComponent.lock()->SetTexture("ground.jpg", 0);
	// renderComponent.lock()->SetShader("shader/pstest.fx", shader::ShaderType::PS);
	// renderComponent.lock()->SetShader("shader/Geometry/gs.fx", shader::ShaderType::GS);

	CreateUpdateFunction(GROUND_UPDATE_NAME, &GameObjectGround::GroundUpdate, this);
	SetUpdateFunction(GROUND_UPDATE_NAME);

	m_rotate = math::Vector3(0.f, 0.f, 0.f);
	m_scale = math::Vector3(1.f, 1.f, 1.f);
}

void GameObjectGround::ImGuiDraw() {
	ImGui::SliderFloat3("GroundPosition", m_position.GetPtr(), -10.f, 10.f);
	ImGui::SliderFloat3("GroundRotate", m_rotate.GetPtr(), -360.f, 360.f);
}

}
}