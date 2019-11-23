#pragma once

#include"./DirectX/DirectX11Manager.h"
#include "./Renderer/DirectXRenderManager.h"
#include "./MyDirectXCamera.h"
#include "./MyDirectXLight.h"

#include <memory>

class FpsManager;

namespace mslib {
	namespace directx {
		class DirectX11Manager;

	}
}

namespace Game {
	class GameLoop {
	public:
		GameLoop(mslib::directx::DirectX11Manager * _directx_manager);

		~GameLoop();

		void Init();

		void Update();

		void Render();

		void ImGuiRender();

		void Exit();

	private:
		mslib::directx::DirectX11Manager *m_directx11_manager;
		// MyDirectX11::Render::DirectXRender *m_directx_render;

		std::unique_ptr<FpsManager> m_fps_manager;

		//ÉJÉÅÉâÇÃê∂ê¨
		mslib::Camera::Camera m_camera;
		mslib::Light::ParallelLight m_light;

		void RenderAfter();
		void RenderBefore();

		void ImGuiRenderAfter();
		void ImGuiRenderBefor();

		void RenderSetShaders();

		void PostEffect();

	};
}