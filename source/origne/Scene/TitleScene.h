#pragma once

#include "./core/Scene/basescene.h"
#include "../Camera/HaveCameraGameObject.h"
#include "./origne/Title/TitleSceneManagerGameObject.h"

namespace mslib {
namespace scene {
class TitleScene :public BaseScene {
public:
	void Update()override;
	void Load()override;
	void UnLoad()override;
private:
	object::HaveCameraGameObjectSPtr m_haveCamera;
	object::TitleSceneManagerGameObjectSPtr m_titleSceneManager;
};
}
}