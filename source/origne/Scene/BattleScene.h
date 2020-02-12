#pragma once
#include "./core/Scene/basescene.h"

namespace mslib {
namespace scene {

class BattleScene :public BaseScene {
public:
	BattleScene() = default;
	~BattleScene() = default;

	void Load()override;
private:
	void Update()override;
};
}
}
