#include "./BattleScene.h"
#include <./origne/RPGManager/GameObject/RpgManagerGameObject.h>
#include <./origne/RPGManager/GameObject/RpgFieldGameObject.h>



namespace mslib {
namespace scene {
void BattleScene::Update() {
	// AllObjectUpdate();
}

void BattleScene::Load() {
	auto heveCameraGameObject = TYPE_FIND_GAME_OBJECT(object::HaveCameraGameObject, "HaveCameraGameObject");
	auto _playerGameObject = TYPE_FIND_GAME_OBJECT(origin::game::PlayerGameObject, "PlayerGameObject");
	auto _enemyManagerGameObject = TYPE_FIND_GAME_OBJECT(object::EnemyManagerGameObject, "EnemyManagerGameObject");

	CREATE_GAME_OBJECT(origin::manager::RpgManagerGameObject, heveCameraGameObject, _playerGameObject, _enemyManagerGameObject);
	CREATE_GAME_OBJECT(object::RpgFieldGameObject);
}

}
}