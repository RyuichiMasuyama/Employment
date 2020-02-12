#include "./TitleScene.h"
#include "./GameObjectManager.h"



namespace mslib {
namespace scene {
void TitleScene::Update() {
	// AllObjectUpdate();
}
void TitleScene::Load() {
	auto _haveCamera  = CREATE_GAME_OBJECT(object::HaveCameraGameObject);
	m_titleSceneManager = CREATE_GAME_OBJECT(object::TitleSceneManagerGameObject, _haveCamera);
	//IncetanceObject(_haveCamera);
}
void TitleScene::UnLoad() {
	DELETE_GAME_OBJECT(m_titleSceneManager);
}
}
}