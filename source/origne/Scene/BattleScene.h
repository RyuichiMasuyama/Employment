#pragma once
#include "./core/Scene/basescene.h"

namespace mslib {
namespace scene {

class BattleScene :public BaseScene {
public:
	BattleScene() = default;
	~BattleScene() = default;
private:
	void Update()override;
	void Load()override;
};
}
}
