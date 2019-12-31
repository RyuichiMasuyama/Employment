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

void HaveCameraGameObject::Initialize() {
	base::Initialize();

	CreateUpdateFunction(TestUpdateName, &HaveCameraGameObject::TestUpdate, this);
	SetUpdateFunction(TestUpdateName);

	// カメラをセット
	auto cameraCom = AddComponent<component::CameraComponent>();
	m_feadComponent = AddComponent<component::FeadComponent>("dizonbul.jpg");
	// ポストエフェクトを追加
	 m_postEffect = cameraCom.lock()->AddPostEffectComponent<component::BasePostEffectComponent>();
	m_position = math::Vector3(2.f, 2.f, -2.f);

	m_feadLevel = 0.f;
}

void HaveCameraGameObject::ImGuiDraw() {
	ImGui::SliderFloat3("CameraPos", m_position.GetPtr(), -100.f, 100.f);
	ImGui::SliderFloat3("CameraRot", m_rotate.GetPtr(), -360.f, 360.f);

	ImGui::SliderFloat("Gauus", &m_gauusePower, 0.f, 1.f);
	ImGui::Checkbox("GaussFlag",&m_gauuseFlag);

	ImGui::SliderFloat("Bloom", &m_bloomPower, 0.f, 1.f);
	ImGui::Checkbox("BloomFlag", &m_bloomFlag);

	ImGui::SliderFloat("Fead", &m_feadLevel, 0.f, 1.f);

	//m_postEffect.lock()->SetPostEffectFlag(m_gauuseFlag, render::POSTEFFECT_TYPE::GAUSS);
	//m_postEffect.lock()->SetGauusePower(m_gauusePower);
}

void HaveCameraGameObject::TestUpdate() {
	if (input::Input::GetKeyStay(MSK_W)) {
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
	m_feadComponent.lock()->SetFeadLevel(m_feadLevel);
}

}
}
