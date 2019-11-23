#pragma once
#include "./core/Object/Object.h"
namespace mslib {
namespace origin {

class DepseBuffer2DRenderGameObject :public object::GameObject{
	BASE_CLASS_IS(GameObject)
public:
	static constexpr const char* TestUpdateName = "TestUpdate";

	void Initialize() override;

	void ImGuiDraw()override;
private:
	void TestUpdate();
};

}
}