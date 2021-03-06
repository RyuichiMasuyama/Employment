#include "./GameLoopManager.h"
#include "./GameObjectManager.h"

#include "./Renderer/Render.h" 

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

namespace mslib {
GameLoop::GameLoop(){
	//m_directx11_manager = _directx_manager;

	//m_fpsManager = std::make_unique<FpsManager>(_directx_manager);

	// カメラ変換行列初期化
	// プロジェクション変換行列初期化
	//math::Vector3 eye = { 0.f,0.f,-10.f };				// 視点
	//math::Vector3 lookat = { 0,0,0 };			// 注視点
	//math::Vector3 up = { 0,1,0 };					// 上向きベクトル

	//m_camera.Init(1.0f, 10000.0f, DirectX::XM_PIDIV2, SCREEN_X, SCREEN_Y, eye, lookat, up);
}

GameLoop::~GameLoop() = default;

void GameLoop::Init() {}

void GameLoop::Exit() {
}

void GameLoop::RenderAfter() {
	// swap
	directx::DirectX11Manager::GetInstance().GetSwapChain()->Present(0, 0);
}

void GameLoop::RenderBefore() {
	////バックカラー
	//float color[4] = { 0.f,0.f,1.f,1.f };

	//m_directx11_manager->GetDeviceContext()->OMSetRenderTargets(1, m_directx11_manager->GetRenderTargetView().GetAddressOf(),
	//	m_directx11_manager->GetDepthStencilView().Get());

	//// ターゲットバッファクリア
	//m_directx11_manager->GetDeviceContext()->ClearRenderTargetView(m_directx11_manager->GetRenderTargetView().Get(), color);

	//// Zバッファクリア
	//m_directx11_manager->GetDeviceContext()->ClearDepthStencilView(m_directx11_manager->GetDepthStencilView().Get(),
	//	D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

	////プリミティブトポロジーをセット
	//m_directx11_manager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	////アルファブレンドオン
	//m_directx11_manager->TurnOnAlphaBlending();
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

	//ジオメトリシェーダーをセット
	//m_directx11_manager->GetDeviceContext()->GSSetShader(nullptr, nullptr, 0);

	////ハルシェーダーをセット
	//m_directx11_manager->GetDeviceContext()->HSSetShader(nullptr, nullptr, 0);

	////ドメインシェーダーをセット
	//m_directx11_manager->GetDeviceContext()->DSSetShader(nullptr, nullptr, 0);

	// ImGui::Spacing();

#endif // !_DEBUG
}


void GameLoop::Update() {
	//FPSの制御
	m_fpsManager.Update();

	// オブジェクトのアップデート
	mslib::manager::GameObjectManager::GetInstance().Update();

	if (m_fpsManager.GetFixedFlag()) {
		mslib::manager::GameObjectManager::GetInstance().FixedUpdate();
	}
}

void GameLoop::Render() {
	if (m_fpsManager.GetFixedFlag()) {
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
#ifndef _DEBUG
#else
	ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver); 
	ImGui::Begin("aaa", nullptr);
	ImGui::Text("aaaa");
	ImGui::End();
#endif // !_DEBUG
}

}