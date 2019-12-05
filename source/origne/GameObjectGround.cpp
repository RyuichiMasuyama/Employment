#include "./GameObjectGround.h"
#include "./ImGui/imgui.h"
#include "./core/Component/Render/RenderComponent.h"
#include "./AssetManager/MeshLoader.h"

namespace mslib {
namespace origin {

void GameObjectGround::Initialize() {
	base::Initialize();

	mesh::MeshLoader loader;
	AddComponent<component::RenderComponent>(loader.Load("assets/ground.mobj"));

	CreateUpdateFunction(GROUND_UPDATE_NAME, &GameObjectGround::GroundUpdate, this);
	SetUpdateFunction(GROUND_UPDATE_NAME);

	m_rotate = math::Vector3(0.f, -90.f, 90.f);
	m_scale = math::Vector3(10.f, 10.f, 1.f);
}

void GameObjectGround::ImGuiDraw() {
	ImGui::SliderFloat3("GroundPosition", m_position.GetPtr(), -100.f, 100.f);
	ImGui::SliderFloat3("GroundRotate", m_rotate.GetPtr(), -360.f, 360.f);
}

}
}