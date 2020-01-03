#pragma once

#ifndef TEST_GAME_OBJECT_H_
#define TEST_GAME_OBJECT_H_

#include "./core/Object/object.h"
#include "./imgui/imgui.h"
#include "./Renderer/Model.h"
#include "./core/Component/PostEffect/BasePostEffectComponent.h"

namespace mslib {
namespace component {
class FeadComponent;
using FeadComponentPtr = std::weak_ptr<FeadComponent>;
}
namespace origin {

class TestGameObject :public object::GameObject {
	BASE_CLASS_IS(GameObject)
public:
	static constexpr const char* TestUpdateName = "TestUpdate";

	void Initialize() override;

	void ImGuiDraw() override;


private:
	render::ModelData m_modelData;
	mslib::directx::ConstantBuffer buff;
	void TestUpdate();

	float gauuse = 1.f;
};

}
}

#endif // TEST_GAME_OBJECT_H_
