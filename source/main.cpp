// ------------------------------------------------------------------------------
// 	DirectX11初期化全部やり直し勉強
// ------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS

// メモリリーク検出用
#define _CRTDBG_MAP_ALLOC

// C++標準
#include <stdio.h>

// WinMain生成用
#include <Windows.h>

// WindowProcedureを含むクラス
#include "./Windows/WindowsManager.h"

// MyDirextX11関係のクラス
#include "./DirectX/DirectX11Manager.h"
#include "./Renderer/DirectXRenderManager.h"
#include "./Shader/Shader.h"
#include "./MyDirectXTransform.h"
#include "./DirectX/DirectXTextureManager.h"

// Game関係のクラス
#include "./core/GameLoopManager.h"

// Scene管理系のクラス
#include "./core/Scene/SceneManager.h"
#include "./TestScene.h"

#include <ImGui/ImGuiManager.h>

// -----------------------------------------------------------------------------
//  リンクライブラリの設定
// -----------------------------------------------------------------------------
#pragma comment(lib, "d3d11.lib")			// リンク対象ライブラリにd3d11.libを追加
#pragma comment(lib, "dxgi.lib")			// リンク対象ライブラリにdxgxi.libを追加
#pragma comment(lib, "D3DCompiler.lib")		// リンク対象ライブラリにd3dcompiler.libを追加
#pragma comment(lib, "winmm.lib")			// リンク対象ライブラリにwinmm.libを追加

// -----------------------------------------------------------------------------
//  プロトタイプ宣言
// -----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// メッセージ構造体
	MSG	msg;						

	// メモリリークを検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	 
	//ウインドウの生成・初期化+
	mslib::windows::MainWindows win(hInstance);

	// DirectX生成後ウィンドウ表示
	win.ShowMyWindow(nCmdShow);

	// DirectX11の使用・初期化
	mslib::directx::DirectX11Manager& directx = mslib::directx::DirectX11Manager::GetInstance();
	mslib::directx::DirectX11Manager::GetInstance().Init(win.GetHandolWindow(), false);

	// モデル倉庫の生成
	static mslib::render::DirectXRenderObjectWarehouse directx_render_object_warehouse;

	// シェーダーの生成
	static mslib::directx::ShaderWark shader_wark(mslib::directx::DirectX11Manager::GetInstance().GetDevice());

	// テクスチャのローダー
	static mslib::texture::TextureLoder texture_loader(mslib::directx::DirectX11Manager::GetInstance().GetDevice(),
		mslib::directx::DirectX11Manager::GetInstance().GetDeviceContext());

	// モデルローダー生成
	static mslib::render::DirectXRenderObjectLoder directx_render_object_loder(directx.GetDevice(), &shader_wark, &directx_render_object_warehouse, &texture_loader);

	// 描画関係で必要になるマトリックスを送るクラス
	mslib::Transform::TransformSendContext& transform_send_context = mslib::Transform::TransformSendContext::GetInstance();

	transform_send_context.Init(directx.GetDevice(), directx.GetDeviceContext());

	// ImGuiのセットアップ
	ImGuiSetUp(win.GetHandolWindow(), directx.GetDevice().Get(), directx.GetDeviceContext().Get());

	// レンダー
	mslib::render::DirectXRender& m_directx_render = mslib::render::DirectXRender::GetInstance();
	mslib::render::DirectXRender::GetInstance().Initialize(&directx, &directx_render_object_warehouse);

	// ゲームループの作成
	static Game::GameLoop game_loop(&directx);
	
	// シーンマネージャー生成
	static mslib::scene::SceneManager& sceneManager = mslib::scene::SceneManager::GetInstance();

	shader_wark.Create(); 

	directx_render_object_loder.LoadRenderObjectTest();

	game_loop.Init();

	// シーンの生成
	mslib::scene::SceneManager::GetInstance().CreateScnen<mslib::scene::TestScene>();
	
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	{  // メッセージを取得しなかった場合"0"を返す
		// Windowsの処理
			if (msg.message == WM_QUIT) {  // PostQuitMessage()が呼ばれて、WM_QUITメッセージが来たらループ終了
				break;
			} else {
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			game_loop.Update();

			game_loop.Render();

			// game_loop.ImGuiRender();
		}

	}

	game_loop.Exit();

	ImGuiCreanUp();

	return (int)msg.wParam;
}

