#include "./GameObjectLight.h"
#include <imgui\imgui.h>
#include "./core/Component/Camera/ShadowMapCameraComponent.h"

namespace mslib {
namespace origin {

void GameObjectLight::Initialize() {
	base::Initialize();
		
	CreateUpdateFunction(GROUND_UPDATE_NAME, &GameObjectLight::LightUpdate, this);
	SetUpdateFunction(GROUND_UPDATE_NAME);

	auto light = AddComponent<component::DirectionalLightComponent>();
	light.lock()->AddShadowMapComponent < component::ShadowMapCameraComponent >();
	m_lightComponent = light;

	m_rotate.x = -90.f;
}

void GameObjectLight::ImGuiDraw() {
	ImGui::SliderFloat3("LightRot", m_rotate.GetPtr(), -360.f, 360.f);
	ImGui::SliderFloat3("LightPos", m_position.GetPtr(), -100.f, 100.f);
	ImGui::ColorEdit4("LightColor", m_lightComponent.lock()->m_color.GetPtr());
}

}
}
