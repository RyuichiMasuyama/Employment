#pragma once

#include "./FpsManager.h"

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
	FpsManager m_fpsManager;

	void RenderAfter();
	void RenderBefore();

	void ImGuiRenderAfter();
	void ImGuiRenderBefor();
};
}