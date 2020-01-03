
#include "./HaveCameraGameObject.h"
#include "./core/Component/Camera/CameraComponent.h"

#include "./../Fead/FeadComponent.h"

#include "./core/Input/Input.h"

#include <./ImGui/imgui.h>

namespace mslib {
namespace object {

void HaveCameraGameObject::Initialize() {
	base::Initialize();

	CreateUpdateFunction(TestUpdateName, &HaveCameraGameObject::TestUpdate, this);
	SetUpdateFunction(TestUpdateName);

	// カメラをセット
	auto cameraCom = AddComponent<component::CameraComponent>();
	m_feadComponent = AddComponent<component::FeadComponent>("fead.jpg");
	// ポストエフェクトを追加
	// m_postEffect = cameraCom.lock()->AddPostEffectComponent<component::BasePostEffectComponent>();
	m_position = math::Vector3(2.f, 2.f, -2.f);

	m_feadLevel = 0.f;
}

void HaveCameraGameObject::ImGuiDraw() {
	//ImGui::SliderFloat3("CameraPos", m_position.GetPtr(), -100.f, 100.f);
	//ImGui::SliderFloat3("CameraRot", m_rotate.GetPtr(), -360.f, 360.f);

	//ImGui::SliderFloat("Gauus", &m_gauusePower, 0.f, 1.f);
	//ImGui::Checkbox("GaussFlag", &m_gauuseFlag);

	//ImGui::SliderFloat("Bloom", &m_bloomPower, 0.f, 1.f);
	//ImGui::Checkbox("BloomFlag", &m_bloomFlag);

	ImGui::SliderFloat("Fead", &m_feadLevel, 0.f, 1.f);

	//m_postEffect.lock()->SetPostEffectFlag(m_gauuseFlag, render::POSTEFFECT_TYPE::GAUSS);
	//m_postEffect.lock()->SetGauusePower(m_gauusePower);
}

void HaveCameraGameObject::SetFeadLevel(float _feadLevel) {
	m_feadComponent.lock()->SetFeadLevel(_feadLevel);
}

void HaveCameraGameObject::TestUpdate() {
	if (input::Input::GetKeyEnter(MSK_W)) {
		m_position += m_matrix.GetFront() * 0.01f;
	};
	if (input::Input::GetKeyStay(MSK_A)) {
		m_position += m_matrix.GetRight() * -0.01f;
	};
	if (input::Input::GetKeyStay(MSK_S)) {
		m_position += m_matrix.GetFront() * -0.01f;
	};
	if (input::Input::GetKeyStay(MSK_D)) {
		m_position += m_matrix.GetRight() * 0.01f;
	};
	// m_feadComponent.lock()->SetFeadLevel(m_feadLevel);
}
}
}