#include "TestGameObject.h"
#include "./AssetManager/MeshLoader.h"
#include "./core/Component/Render/RenderComponent.h"
#include "./core/Component/Camera/CameraComponent.h"
#include "./core/Component/Light/DirectionalLightComponent.h"
#include <ImGui/imgui.h>

#include "./core/Input/Input.h"
#include "./core/Component/Render/ModelRenderComponent.h"
#include "./origne/Fead/FeadComponent.h"

namespace mslib {
namespace origin {

struct PostEffectGause {
	math::Vector4 wight1;
	math::Vector4 wight2;
};

void TestGameObject::Initialize() {
	base::Initialize();

	CreateUpdateFunction(TestUpdateName, &TestGameObject::TestUpdate, this);
	SetUpdateFunction(TestUpdateName);

	/*m_modelData.Load("assets/box.fbx");
	m_modelData.SetVertexShader("shader/vs2d.fx");
	m_modelData.SetPixelShader("shader/ps2d.fx");
	m_modelData.SetTexture("Dragon_Bump_Col2.jpg", 0);*/

	//loader::MeshLoader load;
	//loader::TextureLoader textureLoader;
	auto renderComponent = AddComponent<component::ModelRenderComponent>(&m_modelData);
	//loader::MeshLoader meshLoader;
	//AddComponent<component::RenderComponent>(meshLoader.Load("assets/dragon.msobj"));
}

void TestGameObject::ImGuiDraw() {
	ImGui::SliderFloat3("Position", m_position.GetPtr(), -100.f, 100.f);
	ImGui::SliderFloat3("Roteta", m_rotate.GetPtr(), -360.f, 360.f);
	ImGui::SliderFloat3("Scale", m_scale.GetPtr(), 0.1f, 10.f);
	ImGui::SliderFloat("Gauss", &gauuse, 0.f, 1.f);
}
void TestGameObject::TestUpdate() {
}

}
}
