#include "./TestScene.h"
#include "./TestGameObject.h"
#include "./GameObjectManager.h"
#include "./DepseBufferRender2DGameObject.h"
#include "./origne/GameObjectGround.h"
#include "./origne/GameObjectLight.h"

// origin��RPG�����̃C���N���[�h
#include "./origne/RPGManager/GameObject/RpgManagerGameObject.h"
#include "./origne/Player/GameObject/PlayerGameObject.h"

namespace mslib {
namespace scene {

void TestScene::Update() {
	// AllObjectUpdate();
}

void TestScene::Draw() {
}

void TestScene::ImGuiDraw() {
}

void TestScene::Load() {
	//<origin::TestGameObject>();
	// CREATE_GAME_OBJECT(origin::TestGameObject)
	// CREATE_GAME_OBJECT(origin::DepseBuffer2DRenderGameObject)
	// CREATE_GAME_OBJECT(origin::HaveCameraGameObject)
	/*CREATE_GAME_OBJECT(origin::GameObjectGround)
	CREATE_GAME_OBJECT(origin::GameObjectLight)
	CREATE_GAME_OBJECT(origin::manager::RpgManagerGameObject)*/
	//CREATE_GAME_OBJECT(origin::game::PlayerGameObject)
}

void TestScene::UnLoad() {
}

}
}