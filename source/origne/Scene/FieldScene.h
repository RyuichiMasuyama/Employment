#pragma once

#include "./core/Scene/basescene.h"

namespace mslib {
namespace scene {

class FieldScene :public BaseScene {
public:
	FieldScene() = default;
	~FieldScene() = default;

	void Update()override;
	void Load()override;
};
}
}
