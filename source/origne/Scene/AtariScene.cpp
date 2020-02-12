#include "./AtariScene.h"
#include "./GameObjectManager.h"
#include <./origne/Atari/FpsDrawGameObject.h>
#include <./origne/Atari/AtariGameObject.h>

namespace mslib {
namespace scene {
void AtariScene::Update() {
}

void AtariScene::Load() {
	auto _haveCamera = CREATE_GAME_OBJECT(object::HaveCameraGameObject);
	CREATE_GAME_OBJECT(object::FpsDrawGameObject);

	int incetanceSize = 1800;
	for (int i = 0; i < incetanceSize; i++)
		CREATE_GAME_OBJECT(object::AtariGameObject);
}

void AtariScene::UnLoad() {
}
}
}