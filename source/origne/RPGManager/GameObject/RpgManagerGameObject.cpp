#include "./RpgManagerGameObject.h"
#include "../Component/RpgManagerComponent.h"
#include <./core/FpsManager.h>


namespace mslib {
namespace origin {
namespace manager {
RpgManagerGameObject::RpgManagerGameObject(
	object::HaveCameraGameObjectSPtr _haveCameraGameObject,
	origin::game::PlayerGameObjectSPtr _playerGameObject,
	object::EnemyManagerGameObjectSPtr _enemyManagerGameObject) :
m_haveCameraGameObject(_haveCameraGameObject),
m_playerGameObject(_playerGameObject),
m_enemyManagerGameObject(_enemyManagerGameObject){
}
void RpgManagerGameObject::Initialize() {
	base::Initialize();

	m_rpgManagerCompoent = AddComponent<RpgManagerComponent>(static_cast<int>(BATTLE_PHASE::Player));
	m_feadLevel = 1.f;
	CreateUpdateFunction(RpgUpdateName, &RpgManagerGameObject::RpgUpdate, this);
	SetUpdateFunction(RpgUpdateName);

	auto playerTransform = m_playerGameObject->m_transform;

	m_playerFiledMatrix = playerTransform->m_matrix;

	playerTransform->m_position = math::Vector3(0.f, 0.f, 0.f);
	playerTransform->m_rotate = math::Vector3(0.f, 0.f, 0.f);
}
void RpgManagerGameObject::RpgUpdate() {
	m_feadLevel -= FpsManager::GetInstance().GetDeltaTime();
	m_haveCameraGameObject->SetFeadLevel(m_feadLevel);

	//m_playerGameObject->
}

void RpgManagerGameObject::BeforUpdate() {
	
}

}
}
}