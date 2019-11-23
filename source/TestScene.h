#pragma once

#include "./core/Scene/basescene.h"

namespace mslib {
namespace scene {

class TestScene :public BaseScene {
public: 
	void Update() override;
	void Draw() override;
	void ImGuiDraw() override;

	void Load()override;
	void UnLoad()override;
public:


};

}
}