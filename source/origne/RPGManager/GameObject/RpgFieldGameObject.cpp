#include "./RpgFieldGameObject.h"
#include <ImGui/imgui.h>

namespace mslib {
namespace object {

void RpgFieldGameObject::Initialize() {
	base::Initialize();

	m_modelData.Load("assets/battleField.fbx");
	m_modelData.SetVertexShader("shader/testvs.fx");
	m_modelData.SetPixelShader("shader/ps2d.fx");
	m_modelData.SetTexture("battleField.jpg", 0);

	AddComponent<component::ModelRenderComponent>(&m_modelData);

	m_rotate = math::Vector3(90, 90, 0);
	m_scale = math::Vector3(100, 100, 100);
}

void RpgFieldGameObject::ImGuiDraw() {
	ImGui::SliderFloat3("FieldPosition", m_position.GetPtr(), -1000.f, 1000.f);
	ImGui::SliderFloat3("FieldScale", m_scale.GetPtr(), -1000.f, 1000.f);
	ImGui::SliderFloat3("FieldRotate", m_rotate.GetPtr(), -360.f, 360.f);
}

}
}