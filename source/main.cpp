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

#include "./core/Input/Input.h"

// WindowProcedureを含むクラス
#include "./Windows/WindowsManager.h"

// MyDirextX11関係のクラス
#include "./DirectX/DirectX11Manager.h"

// Scene管理系のクラス
#include "./core/Scene/SceneManager.h"
#include "./TestScene.h"

#include "./core/GameLoopManager.h"

#include <ImGui/ImGuiManager.h>

#include <any>

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
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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

	// ImGuiのセットアップ
	ImGuiSetUp(win.GetHandolWindow(), directx.GetDevice().Get(), directx.GetDeviceContext().Get());

	// シーンマネージャー生成・シーンの生成
	static mslib::scene::SceneManager& sceneManager = mslib::scene::SceneManager::GetInstance();
	mslib::scene::SceneManager::GetInstance().CreateScnen<mslib::scene::TestScene>();

	// キー操作の生成
	mslib::input::Input input(hInstance);

	// ゲームループの作成
	mslib::GameLoop gameLoop;
	gameLoop.Init();

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
			gameLoop.Update();

			input.Update();

			gameLoop.Render();
		}
	}

	gameLoop.Exit();

	ImGuiCreanUp();

	return (int)msg.wParam;
}

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	// メッセージ構造体
//	MSG	msg;
//
//	// メモリリークを検知
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//	//ウインドウの生成・初期化+
//	mslib::windows::MainWindows win(hInstance);
//
//	// DirectX生成後ウ1ィンドウ表示
//	win.ShowMyWindow(nCmdShow);
//
//	mslib::directx::DirectX11Manager::GetInstance().Init(win.GetHandolWindow(), false);
//	mslib::shader::ShaderLoader loader; 
//	{
//		std::any ps;
//		{
//			mslib::directx::PixelShader aa;
//
//			loader.Load("shader/PSGauss.fx", aa, mslib::shader::ShaderType::PS);
//
//			ps = aa;
//
//			aa.Reset();
//
//			mslib::directx::PixelShader bb;
//			bb = std::any_cast<mslib::directx::PixelShader>(ps);
//
//			mslib::directx::DirectX11Manager::GetInstance().GetDeviceContext()->PSSetShader(bb.Get(), nullptr, 1);
//		}
//	}
//	rewind(stdin);
//	getchar();
//
//}

