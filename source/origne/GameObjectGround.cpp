#include "./GameObjectGround.h"
#include "./ImGui/imgui.h"
#include "./core/Component/Render/RenderComponent.h"
#include "./AssetManager/MeshLoader.h"

namespace mslib {
namespace origin {

void GameObjectGround::Initialize() {
	base::Initialize();

	loader::MeshLoader load;
	auto renderComponent = AddComponent<component::RenderComponent>(load.Load("assets/testGround.msobj"));
	renderComponent.lock()->SetTexture("ground.jpg", 0);
	renderComponent.lock()->SetShader("shader/pstest.fx", shader::ShaderType::PS);
	renderComponent.lock()->SetShader("shader/Geometry/gs.fx", shader::ShaderType::GS);

	CreateUpdateFunction(GROUND_UPDATE_NAME, &GameObjectGround::GroundUpdate, this);
	SetUpdateFunction(GROUND_UPDATE_NAME);

	m_rotate = math::Vector3(0.f, 180.f, 0.f);
	m_scale = math::Vector3(1.f, 1.f, 1.f);
}

void GameObjectGround::ImGuiDraw() {
	ImGui::SliderFloat3("GroundPosition", m_position.GetPtr(), -10000.f, 10000.f);
	ImGui::SliderFloat3("GroundRotate", m_rotate.GetPtr(), -360.f, 360.f);
}

}
}