#pragma once

//ウィンドウ作成のため
#include <Windows.h>

//標準
#include <stdio.h>
#include <stdlib.h>

namespace mslib {
namespace windows {

#define		FULLSCREEN		0				// フルスクリーンフラグ

	class MainWindows {
	private:
		HWND			m_hwnd;						// ウインドウハンドル
		MSG				m_msg;						// メッセージ構造体
		WNDCLASSEX		m_wcex;						// ウインドウクラス構造体

		int				m_width;					// ウインドウの幅 計算用ワーク
		int				m_height;					// ウインドウの高さ 計算用ワーク

		bool InitWndClass(HINSTANCE hInstance);		//ウィンドウクラスの構造体生成

		bool CreateMyWindow(HINSTANCE _hInstance);	//クリエイトウィンドウを使う

	public:
		MainWindows(HINSTANCE 	hInstance);			//コンストラクタ
		~MainWindows();								//デストラクタ

		void ShowMyWindow(int nWinMode);

		HWND GetHandolWindow();
		
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);			// ウインドウプロシージャ

	};
}
}