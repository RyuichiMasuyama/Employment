#pragma once

#include "./core/Scene/basescene.h"

namespace mslib {
namespace scene {
class TitleScene :public BaseScene {
public:
	TitleScene() = default;
	~TitleScene() = default;

private:
	void Load()override;
};
}
}