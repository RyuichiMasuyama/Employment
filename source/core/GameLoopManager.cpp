#include "./GameLoopManager.h"
#include "./GameObjectManager.h"

#include <./core/CollisionManager.h>

#include "./Renderer/Render.h" 

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

namespace mslib {
GameLoop::GameLoop(){
}

GameLoop::~GameLoop() = default;

void GameLoop::Init() {
	manager::CollisionManager::GetInstance().Initialize(
		7,
		COLLISION_THREE_SIZE_MIN,
		COLLISION_THREE_SIZE_MAX);
}

void GameLoop::Exit() {
}

void GameLoop::RenderAfter() {
	// swap
	directx::DirectX11Manager::GetInstance().GetSwapChain()->Present(0, 0);
}

void GameLoop::RenderBefore() {
}

void GameLoop::ImGuiRenderAfter() {
#ifndef _DEBUG
#else
	ImGui::Render();        
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif // !_DEBUG
}

void GameLoop::ImGuiRenderBefor() {
#ifndef _DEBUG
#else
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
#endif // !_DEBUG
}


void GameLoop::Update() {
	//FPSの制御
	FpsManager::GetInstance().Update();

	// オブジェクトのアップデート
	mslib::manager::GameObjectManager::GetInstance().Update();

	if (FpsManager::GetInstance().GetFixedFlag()) {
		mslib::manager::GameObjectManager::GetInstance().FixedUpdate();
	}
}

void GameLoop::Render() {
	if (FpsManager::GetInstance().GetFixedFlag()) {
		// m_directx_render->Render();	
		mslib::render::Render::GetInstance().Rendering();

		// RenderBefore();

		//mslib::directx::DirectXRender::GetInstance().RenderQuad();

		mslib::render::Render::GetInstance().ImGuiCare();

		ImGuiRenderBefor();

		// ImGuiRender();

		mslib::manager::GameObjectManager::GetInstance().ShowImGui();

		ImGuiRenderAfter();

		RenderAfter();
	}
}

void GameLoop::ImGuiRender() {
#ifdef _DEBUG
	ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver); 
	ImGui::Begin("aaa", nullptr);
	ImGui::Text("aaaa");
	ImGui::End();
#endif // !_DEBUG
}

}