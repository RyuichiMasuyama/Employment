#pragma once

#include "./core/Scene/basescene.h"
#include "./origne/Field/FieldManager.h"
#include "./origne/Player/GameObject/PlayerGameObject.h"
#include <./origne/Camera/HaveCameraGameObject.h>
#include <./origne/Field/Field.h>
#include <./origne/Enemy/GameObject/EnemyManagerGameObject.h>


namespace mslib {
namespace scene {

class FieldScene :public BaseScene {
public:
	FieldScene() = default;
	~FieldScene() = default;

	void Update()override;
	void Load()override;

	void UnActive()override;
private:
	origin::game::PlayerGameObjectSPtr m_playerGameObject;// = CREATE_GAME_OBJECT(origin::game::PlayerGameObject, haveCamera);
	manager::FieldManagerGameObjectSPtr m_fieldManagerGameObject;// = CREATE_GAME_OBJECT(manager::FieldManagerGameObject, playerGameObject, haveCamera);
	object::FieldGameObjectSPtr m_fieldObject;// = CREATE_GAME_OBJECT(object::FieldGameObject);
	object::EnemyManagerGameObjectSPtr m_enemyManagerGameObject;// = CREATE_GAME_OBJECT(object::EnemyManagerGameObject);
};
}
}
