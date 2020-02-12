#include "./FieldManager.h"
#include <./core/FpsManager.h>
#include "./FieldManagerComponent.h"

#include <./core/scene/SceneManager.h>
#include <./origne/scene/BattleScene.h>

namespace mslib {
namespace manager {
FieldManagerGameObject::FieldManagerGameObject(origin::game::PlayerGameObjectPtr _playerGameObjectPtr, object::HaveCameraGameObjectPtr _haveCameraGameObjectPtr)
:m_playerGameObjectPtr(_playerGameObjectPtr),
m_haveCameraGameObjectPtr(_haveCameraGameObjectPtr){
}

void FieldManagerGameObject::Initialize() {
	base::Initialize();
	
	m_feadLevel = 1.f; 
	m_feadIn = true;
	m_feadOut = false;
	m_enemyEnter = false;
	m_sceneChange = false;

	CreateUpdateFunction(FieldUpdateName, &FieldManagerGameObject::FieldUpdate, this);
	AddComponent<component::FieldManagerComponent>(m_sceneChange);
	SetUpdateFunction(FieldUpdateName);
}

void FieldManagerGameObject::ImGuiDraw() {
	m_enemyEnter = ImGui::Button("EnemyEnter");
}

void FieldManagerGameObject::AfterUpdate() {
}

void FieldManagerGameObject::FieldUpdate() {
	if (m_feadIn) {
		if (FpsManager::GetInstance().GetDeltaTime() < 1.f) {
			m_feadLevel -= FpsManager::GetInstance().GetDeltaTime();
		}
		if (m_feadLevel < 0.f) {
			m_feadLevel = 0.f;
			m_feadIn = false;
		}
	}

	m_haveCameraGameObjectPtr.lock()->SetFeadLevel(m_feadLevel);

	if (m_enemyEnter) {
		m_feadOut = true;
		m_playerGameObjectPtr.lock()->Encount();
	}
	if (m_feadOut) {
		m_feadLevel += FpsManager::GetInstance().GetDeltaTime();
		if (1.f < m_feadLevel) {
			m_sceneChange = true;
			scene::SceneManager::GetInstance().CreateScene<scene::BattleScene>();
			//m_playerGameObjectPtr->;
			// SetActive(false);
		}
	}
}


}
}