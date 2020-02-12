#pragma once

#include <./core/Object/object.h>

namespace mslib {
namespace object {
class FpsDrawGameObject:public GameObject {
	BASE_CLASS_IS(GameObject)
public:
	FpsDrawGameObject() = default;
	~FpsDrawGameObject() = default;

	void Update() override;
	void ImGuiDraw() override;
private:
	float m_fps;
};
}
}