#include "WindowsManager.h"
#include "./Windows/WindowsDefineData.h"

#ifdef _DEBUG

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_impl_dx11.h>

#endif // DEBUG


//メモリリーク検出使用
#include <crtdbg.h>

#ifdef _DEBUG
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif // !_DEBUG

namespace mslib {
namespace windows {
//ウィンドウ構造体の初期化
bool MainWindows::InitWndClass(HINSTANCE _hInstance) {
	//ウィンドウクラス情報のセット
	m_wcex.hInstance = _hInstance;			// インスタンス値のセット
	m_wcex.lpszClassName = NAME;					// クラス名
	m_wcex.lpfnWndProc = (WNDPROC)WndProc;		// ウインドウメッセージ関数
	m_wcex.style = 0;					// ウインドウスタイル
	m_wcex.cbSize = sizeof(WNDCLASSEX);	// 構造体のサイズ
	m_wcex.hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);	// ラージアイコン
	m_wcex.hIconSm = LoadIcon((HINSTANCE)NULL, IDI_WINLOGO);		// スモールアイコン
	m_wcex.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);		// カーソルスタイル
	m_wcex.lpszMenuName = 0; 					// メニューなし
	m_wcex.cbClsExtra = 0;					// エキストラなし
	m_wcex.cbWndExtra = 0;
	m_wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// 背景色白

	if (!RegisterClassEx(&m_wcex)) return FALSE;	// ウインドウクラスの登録
	return TRUE;
}

bool MainWindows::CreateMyWindow(HINSTANCE _hInstance) {
	if (FULLSCREEN) {
		m_hwnd = CreateWindow(
			NAME,							// ウィンドウクラスの名前
			TITLE,							// タイトル
			WS_VISIBLE | WS_POPUP,			// ウィンドウスタイル
			0, 0,							// ウィンドウ位置 縦, 横
			SCREEN_X, SCREEN_Y,				// ウィンドウサイズ
			NULL,							// 親ウィンドウなし
			(HMENU)NULL,					// メニューなし
			_hInstance,						// インスタンスハンドル
			(LPVOID)NULL);					// 追加引数なし
	}
	else {
		RECT	rWindow, rClient;

		m_hwnd = CreateWindow(
			NAME,							// ウィンドウクラスの名前
			TITLE,							// タイトル
			WS_CAPTION | WS_SYSMENU,		// ウィンドウスタイル
			0, 0,							// ウィンドウ位置 縦, 横(あとで中央に移動させます)
			SCREEN_X, SCREEN_Y,				// ウィンドウサイズ
			HWND_DESKTOP,					// 親ウィンドウなし
			(HMENU)NULL,					// メニューなし
			_hInstance,						// インスタンスハンドル
			(LPVOID)NULL);					// 追加引数なし

											// ウインドウサイズを再計算（Metricsだけでは、フレームデザインでクライアント領域サイズが変わってしまうので）
		GetWindowRect(m_hwnd, &rWindow);
		GetClientRect(m_hwnd, &rClient);
		m_width = (rWindow.right - rWindow.left) - (rClient.right - rClient.left) + SCREEN_X;
		m_height = (rWindow.bottom - rWindow.top) - (rClient.bottom - rClient.top) + SCREEN_Y;
		SetWindowPos(
			m_hwnd,
			NULL,
			GetSystemMetrics(SM_CXSCREEN) / 2 - m_width / 2,
			GetSystemMetrics(SM_CYSCREEN) / 2 - m_height / 2,
			m_width - 1,
			m_height - 1,
			SWP_NOZORDER);
	}

	if (!m_hwnd) return FALSE;
	return TRUE;
}

//MainWinsodws
//コンストラクタ
MainWindows::MainWindows(HINSTANCE 	hInstance) {
	//ウィンドウサイズの代入
	m_width = SCREEN_X;
	m_height = SCREEN_Y;

	//ハンドルウィンドウ設定
	InitWndClass(hInstance);

	//ウィンドウの作成
	CreateMyWindow(hInstance);

}

MainWindows::~MainWindows() {
}

void MainWindows::ShowMyWindow(int _nWinMode) {
	// ウインドウを表示する
	ShowWindow(m_hwnd, _nWinMode);
	UpdateWindow(m_hwnd);
}

HWND MainWindows::GetHandolWindow() {
	return m_hwnd;
}

//WindowProcedure
LRESULT MainWindows::WndProc(HWND hwnd, 		// ウィンドウハンドル
	UINT message,	// メッセージ識別子
	WPARAM wParam,	// 付帯情報１
	LPARAM lParam)	// 付帯情報２
{
#ifdef _DEBUG
	if (ImGui_ImplWin32_WndProcHandler(hwnd, message, wParam, lParam))
		return true;
#endif // !_DEBUG

	switch (message) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
}
}