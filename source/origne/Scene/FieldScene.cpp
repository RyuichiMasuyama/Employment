#include "./FieldScene.h"
#include "./GameObjectManager.h"
#include "./origne/Field/FieldManager.h"
#include "./origne/Player/GameObject/PlayerGameObject.h"

namespace mslib {
namespace scene {

void FieldScene::Update() {
	AllObjectUpdate();
}

void FieldScene::Load() {
	CREATE_GAME_OBJECT(manager::FieldManagerGameObject);
	CREATE_GAME_OBJECT(origin::game::PlayerGameObject);
	//CREATE_GAME_OBJECT();
}
}
}