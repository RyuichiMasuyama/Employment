#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace origin {
class GameObjectGround :public object::GameObject{
	BASE_CLASS_IS(object::GameObject)
private:
	static constexpr const char * OBJCTNAME = "GameObjectGround";
	static constexpr const char * GROUND_UPDATE_NAME = "GameObjectGround";

public:
	void Initialize() override;
	void ImGuiDraw()override;
	
	void GroundUpdate() {};
};
}
}