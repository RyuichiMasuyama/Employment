#pragma once

#include "./core/Component/Light/DirectionalLightComponent.h"
#include "./core/Object/object.h"

namespace mslib {
namespace origin {
class GameObjectLight :public object::GameObject {
	BASE_CLASS_IS(object::GameObject)
private:
	static constexpr const char * OBJCTNAME = "GameObjectLight";
	static constexpr const char * GROUND_UPDATE_NAME = "GameObjectLight";

	component::DirectionalLightComponentPtr m_lightComponent;
public:
	void Initialize() override;
	void ImGuiDraw()override;

	void LightUpdate() {};
};
}
}