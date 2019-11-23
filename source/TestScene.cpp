#include "TestScene.h"
#include "TestGameObject.h"
#include "GameObjectManager.h"
#include "DepseBufferRender2DGameObject.h"

namespace mslib {
namespace scene {

void TestScene::Update() {
	AllObjectUpdate();
}

void TestScene::Draw() {
}

void TestScene::ImGuiDraw() {
}

void TestScene::Load() {
	//<origin::TestGameObject>();
	CREATE_GAME_OBJECT(origin::TestGameObject)
	CREATE_GAME_OBJECT(origin::DepseBuffer2DRenderGameObject)
}

void TestScene::UnLoad() {
}

}
}