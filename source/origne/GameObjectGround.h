#pragma once

#include "./core/Object/object.h"
#include "../Renderer/Model.h"

namespace mslib {
namespace render{
class ModelData;
}
namespace origin {
class GameObjectGround :public object::GameObject{
	BASE_CLASS_IS(object::GameObject)
private:
	static constexpr const char * OBJCTNAME = "GameObjectGround";
	static constexpr const char * GROUND_UPDATE_NAME = "GameObjectGround";
	render::ModelData m_modelData;

public:
	void Initialize() override;
	void ImGuiDraw()override;
	
	void GroundUpdate() {};

};
}
}