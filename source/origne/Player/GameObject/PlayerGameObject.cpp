#include "./PlayerGameObject.h"
#include "./AssetManager/ModelLoader.h"
#include "../Component/PlayerRgiComponent.h"
#include "./core/Component/Render/ModelRenderComponent.h"
#include <./core/Input/Input.h>
#include <./core/FpsManager.h>
#include <./ImGui/imgui.h>
#include <./GameObjectManager.h>
#include <./core/Component/Physics/RigidbodyComponent.h>

namespace mslib {
namespace origin {
namespace game {

PlayerGameObject::PlayerGameObject(mslib::object::HaveCameraGameObjectSPtr _cameraObejctPtr) {
	m_cameraObejctPtr = _cameraObejctPtr;
	// m_cameraObejctPtr->m_transform->SetParent(m_transform);
}

void PlayerGameObject::Initialize() {
	base::Initialize();
	SetClassName("PlayerGameObject");

	m_modelData.Load("assets/unitychan.fbx");
	m_modelData.SetTexture("Floor_C.jpg", 0);
	m_modelData.SetPixelShader("shader/ps2d.fx");
	m_modelData.SetVertexShader("shader/testvs.fx");

	AddComponent<component::ModelRenderComponent>(&m_modelData);

	CreateUpdateFunction(RpgUpdateName, &PlayerGameObject::RpgUpdate, this);
	CreateUpdateFunction(FieldUpdateName, &PlayerGameObject::FieldUpdate, this);

	// とりあえずアップデートをFieldからする
	SetUpdateFunction(FieldUpdateName);

	// statusをすべて1で設定
	ZeroMemory(&m_status, sizeof(m_status));

	m_playerRpgComponetPtr = AddComponent<PlayerRpgComponent>(&m_status);
	AddComponent<component::RigidbodyComponent>();

	// とりあえず普通にエンカウント
	m_playerRpgComponetPtr.lock()->SetEncountState(PlayerState::FIELD);

	// Fieldでの移動速度
	m_moveSpd = 1.f;
	m_rotate = math::Vector3(0.f, 0.f, 0.f);

	// カメラの位置補間
	m_rotLength = 10.f;
	m_rot = math::Vector2(0.f, 0.f);

	m_scale = math::Vector3(0.015f, 0.015f, 0.015f);

	// エンカウント
	m_encount = false;

	// コマンドテクスチャ
	{
		std::string textureName[] = {
			"TextureModel1.jpg",
			"TextureModel2.jpg"
		};

		for (auto itr : textureName) {
			auto playerCommand = CREATE_GAME_OBJECT(PlayerCommandModelGameObject, itr);

			m_playerCommandModelGameObjectDynamicArrayPtr.push_back(playerCommand);

			playerCommand->SetActive(false);

			// 親を設定
			playerCommand->m_transform->SetParent(m_transform);
		}
	}
}

void PlayerGameObject::ImGuiDraw() {
	ImGui::SliderFloat("MoveSpeed", &m_moveSpd, 0.1f, 10000.f);
	ImGui::SliderFloat3("CameraPos", m_cameraPos.GetPtr(), -50.f, 50.f);
	ImGui::SliderFloat("CameraLenght", &m_rotLength, 0.1f, 50.f);
}

void PlayerGameObject::Encount() {
	m_encount = true;
}

void PlayerGameObject::RpgUpdate() {

}

void PlayerGameObject::FieldUpdate() {
	float deltaTime = FpsManager::GetInstance().GetDeltaTime();

	if (input::Input::GetKeyEnter(MSK_UP)) {
		m_transform->m_position.z += m_moveSpd *deltaTime;
	}
	if (input::Input::GetKeyEnter(MSK_DOWN)) {
		m_transform->m_position.z -= m_moveSpd *deltaTime;
	}
	if (input::Input::GetKeyEnter(MSK_RIGHT)) {
		m_transform->m_position.x += m_moveSpd *deltaTime;
	}
	if (input::Input::GetKeyEnter(MSK_LEFT)) {
		m_transform->m_position.x -= m_moveSpd *deltaTime;
	}

	if (input::Input::GetKeyEnter(MSK_A)) {
		m_rot.x += deltaTime*60.f;
	}
	if (input::Input::GetKeyEnter(MSK_D)) {
		m_rot.x -= deltaTime * 60.f;
	}
	if (input::Input::GetKeyEnter(MSK_W)) {
		m_rot.y += deltaTime * 60.f;
	}
	if (input::Input::GetKeyEnter(MSK_S)) {
		m_rot.y -= deltaTime * 60.f;
	}

	auto pos = m_transform->m_position;
	
	m_cameraPos.x = sinf(math::ToRadian(m_rot.x)) * m_rotLength;
	m_cameraPos.z = -cosf(math::ToRadian(m_rot.x)) * m_rotLength;
	m_cameraPos.y = sinf(math::ToRadian(m_rot.y)) * m_rotLength;

	pos += m_cameraPos;

	m_cameraObejctPtr->m_transform->m_rotate = math::Vector3(m_rot.y, -m_rot.x, 0.f);
	m_cameraObejctPtr->m_transform->m_rotate.z = 0.f;

	/*pos.z -= 12.f;
	pos.y += 3.f;*/

	m_cameraObejctPtr->m_transform->m_position = pos;
	//m_cameraObejctPtr->m_transform->m_position = math::Vector3(0.f, 0.f, -1000.f);
	if (m_encount) {
		// とりあえず普通にエンカウント
		m_playerRpgComponetPtr.lock()->SetEncountState(PlayerState::ENCOUNTER);
		m_encount = false;
		for (auto itr : m_playerCommandModelGameObjectDynamicArrayPtr) {
			itr->SetActive(true);
		}
	}
}

}  // namespace game
}  // namespace origne
}  // namespace mslib
