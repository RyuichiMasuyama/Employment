
#include "./TitleSceneManagerGameObject.h"
#include "./origne/Camera/HaveCameraGameObject.h"
#include "./core/FpsManager.h"
#include <./core/Scene/SceneManager.h>

#include <./origne/Scene/FieldScene.h>

namespace mslib {
namespace object {

TitleSceneManagerGameObject::TitleSceneManagerGameObject(HaveCameraGameObjectPtr _haveCameraObjectPtr) 
	:m_haveCameraGameObjectPtr(_haveCameraObjectPtr){
}

void TitleSceneManagerGameObject::Initialize() {
	base::Initialize();

	// 初期化
	m_pushAnyKey = false;

	// フェードインの処理
	m_feadLevel = 0.f;
}

void TitleSceneManagerGameObject::Update() {
	if (input::Input::GetAnyEnter()) {
		m_pushAnyKey = true;
	}

	if (m_pushAnyKey) {
		m_feadLevel += FpsManager::GetInstance().GetDeltaTime();
	}

	m_haveCameraGameObjectPtr.lock()->SetFeadLevel(m_feadLevel);

	if (1.f < m_feadLevel) {
		scene::SceneManager::GetInstance().CreateScnen<scene::FieldScene>(true);
	}
}
}
}