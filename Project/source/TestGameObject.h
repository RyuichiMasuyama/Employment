#pragma once

#ifndef TEST_GAME_OBJECT_H_
#define TEST_GAME_OBJECT_H_

#include "./core/Object/object.h"
#include "./imgui/imgui.h"
#include "./DirectX/DirectX11Manager.h"

namespace mslib {
namespace origin {

class TestGameObject :public object::GameObject {
	BASE_CLASS_IS(GameObject)
public:
	static constexpr const char* TestUpdateName = "TestUpdate";

	void Initialize() override;

	void ImGuiDraw() override;


private:
	mslib::directx::ConstantBuffer buff;
	void TestUpdate();

	float gauuse = 1.f;
};

}
}

#endif // TEST_GAME_OBJECT_H_
