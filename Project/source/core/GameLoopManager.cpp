#include "./GameLoopManager.h"
#include "./DirectX/DirectX11Manager.h"
#include "./FpsManager.h"
#include "./Windows/WindowsDefineData.h"
#include "./MyDirectXTransform.h"
#include "./Scene/SceneManager.h"
#include "./GameObjectManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

namespace Game {
GameLoop::GameLoop(mslib::directx::DirectX11Manager * _directx_manager)
	: m_camera(_directx_manager->GetDevice(),
	_directx_manager->GetDeviceContext()), 
	m_light(_directx_manager->GetDevice(),
	_directx_manager->GetDeviceContext()) {

	m_directx11_manager = _directx_manager;

	m_fps_manager = std::make_unique<FpsManager>(_directx_manager);

	// カメラ変換行列初期化
	// プロジェクション変換行列初期化
	math::Vector3 eye = { 0.f,0.f,-10.f };				// 視点
	math::Vector3 lookat = { 0,0,0 };			// 注視点
	math::Vector3 up = { 0,1,0 };					// 上向きベクトル

	m_camera.Init(1.0f, 10000.0f, DirectX::XM_PIDIV2, SCREEN_X, SCREEN_Y, eye, lookat, up);
}

GameLoop::~GameLoop() = default;

void GameLoop::Init() {
	m_light.SetWay(math::Vector4(0.f, 1.f, -1.f, 0.f));
}

void GameLoop::Exit() {
}

void Game::GameLoop::RenderAfter() {
	// swap
	m_directx11_manager->GetSwapChain()->Present(0, 0);
}

void Game::GameLoop::RenderBefore() {
	//バックカラー
	float color[4] = { 0.f,0.f,1.f,1.f };

	m_directx11_manager->GetDeviceContext()->OMSetRenderTargets(1, m_directx11_manager->GetRenderTargetView().GetAddressOf(),
		m_directx11_manager->GetDepthStencilView().Get());

	// ターゲットバッファクリア
	m_directx11_manager->GetDeviceContext()->ClearRenderTargetView(m_directx11_manager->GetRenderTargetView().Get(), color);

	// Zバッファクリア
	m_directx11_manager->GetDeviceContext()->ClearDepthStencilView(m_directx11_manager->GetDepthStencilView().Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

	//プリミティブトポロジーをセット
	m_directx11_manager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//アルファブレンドオン
	m_directx11_manager->TurnOnAlphaBlending();
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
	m_directx11_manager->GetDeviceContext()->GSSetShader(nullptr, nullptr, 0);

	//ハルシェーダーをセット
	m_directx11_manager->GetDeviceContext()->HSSetShader(nullptr, nullptr, 0);

	//ドメインシェーダーをセット
	m_directx11_manager->GetDeviceContext()->DSSetShader(nullptr, nullptr, 0);

	// ImGui::Spacing();

#endif // !_DEBUG
}

void GameLoop::PostEffect() {
}

void GameLoop::Update() {
	//FPSの制御
	m_fps_manager->Update();

	// オブジェクトのアップデート
	mslib::manager::GameObjectManager::GetInstance().Update();

	if (m_fps_manager->GetFixedFlag()) {
		mslib::manager::GameObjectManager::GetInstance().FixedUpdate();
		m_camera.Update();
		m_light.Update();
		PostEffect();
	}
}

void GameLoop::Render() {
	if (m_fps_manager->GetFixedFlag()) {

		// m_directx_render->Render();	
		mslib::render::DirectXRender::GetInstance().Render();

		RenderBefore();

		mslib::render::DirectXRender::GetInstance().RenderQuad();

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