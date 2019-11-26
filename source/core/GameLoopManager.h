#pragma once

#include "./FpsManager.h"
#include <memory>

namespace mslib {
class GameLoop {
public:
	GameLoop();

	~GameLoop();

	void Init();

	void Update();

	void Render();

	void ImGuiRender();

	void Exit();

private:
	FpsManager m_fps_manager;

	void RenderAfter();
	void RenderBefore();

	void ImGuiRenderAfter();
	void ImGuiRenderBefor();


};
}