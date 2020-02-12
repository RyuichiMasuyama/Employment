#include "./FpsDrawGameObject.h"
#include <ImGui/imgui.h>
#include <./core/FpsManager.h>

namespace mslib {
namespace object {

void FpsDrawGameObject::Update() {

}

void FpsDrawGameObject::ImGuiDraw() {
	float fps = FpsManager::GetInstance().GetDeltaTime();
	ImGui::Text("%f", 1.f / fps);
}

}
}