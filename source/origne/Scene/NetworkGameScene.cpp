#include "NetworkGameScene.h"
#include <./origne/Atari/FpsDrawGameObject.h>
#include <origne/NetworkGame/NetworkGame.h>

namespace mslib {
namespace scene {
void NetworkGameScene::Update() {
}

void NetworkGameScene::Load() {
	auto haveCamera = CREATE_GAME_OBJECT(object::HaveCameraGameObject);
	auto networkObject = CREATE_GAME_OBJECT(networkgame::NetworkGameGameObejct);
}

void NetworkGameScene::UnLoad() {
}

}
}