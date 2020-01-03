#include "./TitleScene.h"
#include "../Camera/HaveCameraGameObject.h"
#include "./GameObjectManager.h"



namespace mslib {
namespace scene {
void TitleScene::Update() {
	AllObjectUpdate();
}
void TitleScene::Load() {
	auto  haveCameraObjectPtr = CREATE_GAME_OBJECT(object::HaveCameraGameObject);
	m_titleSceneManager = CREATE_GAME_OBJECT(object::TitleSceneManagerGameObject, haveCameraObjectPtr);
}
void TitleScene::UnLoad() {
	DELETE_GAME_OBJECT(m_titleSceneManager);
}
}
}