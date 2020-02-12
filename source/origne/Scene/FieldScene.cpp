#include "./FieldScene.h"
#include "./GameObjectManager.h"
#include <./origne/SkyBoxGameObject.h>

namespace mslib {
namespace scene {

void FieldScene::Load() {
	auto haveCamera = TYPE_FIND_GAME_OBJECT(object::HaveCameraGameObject, "HaveCameraGameObject");

	m_playerGameObject = CREATE_GAME_OBJECT(origin::game::PlayerGameObject, haveCamera);
	m_fieldManagerGameObject = CREATE_GAME_OBJECT(manager::FieldManagerGameObject, m_playerGameObject, haveCamera);
	m_fieldObject = CREATE_GAME_OBJECT(object::FieldGameObject);
	m_enemyManagerGameObject = CREATE_GAME_OBJECT(object::EnemyManagerGameObject);
	CREATE_GAME_OBJECT(object::SkyBoxGameObject);
}

void FieldScene::UnActive() {
	// m_playerGameObject->SetActive(false); 
	m_fieldManagerGameObject->SetActive(false);
	m_fieldObject->SetActive(false);
	m_enemyManagerGameObject->SetActive(false);
}

void FieldScene::Update() {
	// AllObjectUpdate();
}

}
}