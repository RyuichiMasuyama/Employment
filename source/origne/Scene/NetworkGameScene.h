#pragma once

#include "./core/Scene/basescene.h"
#include "../Camera/HaveCameraGameObject.h"
#include "./origne/Title/TitleSceneManagerGameObject.h"

namespace mslib {
namespace scene {
class NetworkGameScene :public BaseScene {
public:
	void Update()override;
	void Load()override;
	void UnLoad()override;
private:
};
}
}