#include "WindowsManager.h"
#include "./Windows/WindowsDefineData.h"

#ifdef _DEBUG

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_impl_dx11.h>

#endif // DEBUG


//���������[�N���o�g�p
#include <crtdbg.h>

#ifdef _DEBUG
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif // !_DEBUG

namespace mslib {
namespace windows {
//�E�B���h�E�\���̂̏�����
bool MainWindows::InitWndClass(HINSTANCE _hInstance) {
	//�E�B���h�E�N���X���̃Z�b�g
	m_wcex.hInstance = _hInstance;			// �C���X�^���X�l�̃Z�b�g
	m_wcex.lpszClassName = NAME;					// �N���X��
	m_wcex.lpfnWndProc = (WNDPROC)WndProc;		// �E�C���h�E���b�Z�[�W�֐�
	m_wcex.style = 0;					// �E�C���h�E�X�^�C��
	m_wcex.cbSize = sizeof(WNDCLASSEX);	// �\���̂̃T�C�Y
	m_wcex.hIcon = LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);	// ���[�W�A�C�R��
	m_wcex.hIconSm = LoadIcon((HINSTANCE)NULL, IDI_WINLOGO);		// �X���[���A�C�R��
	m_wcex.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);		// �J�[�\���X�^�C��
	m_wcex.lpszMenuName = 0; 					// ���j���[�Ȃ�
	m_wcex.cbClsExtra = 0;					// �G�L�X�g���Ȃ�
	m_wcex.cbWndExtra = 0;
	m_wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// �w�i�F��

	if (!RegisterClassEx(&m_wcex)) return FALSE;	// �E�C���h�E�N���X�̓o�^
	return TRUE;
}

bool MainWindows::CreateMyWindow(HINSTANCE _hInstance) {
	if (FULLSCREEN) {
		m_hwnd = CreateWindow(
			NAME,							// �E�B���h�E�N���X�̖��O
			TITLE,							// �^�C�g��
			WS_VISIBLE | WS_POPUP,			// �E�B���h�E�X�^�C��
			0, 0,							// �E�B���h�E�ʒu �c, ��
			SCREEN_X, SCREEN_Y,				// �E�B���h�E�T�C�Y
			NULL,							// �e�E�B���h�E�Ȃ�
			(HMENU)NULL,					// ���j���[�Ȃ�
			_hInstance,						// �C���X�^���X�n���h��
			(LPVOID)NULL);					// �ǉ������Ȃ�
	}
	else {
		RECT	rWindow, rClient;

		m_hwnd = CreateWindow(
			NAME,							// �E�B���h�E�N���X�̖��O
			TITLE,							// �^�C�g��
			WS_CAPTION | WS_SYSMENU,		// �E�B���h�E�X�^�C��
			0, 0,							// �E�B���h�E�ʒu �c, ��(���ƂŒ����Ɉړ������܂�)
			SCREEN_X, SCREEN_Y,				// �E�B���h�E�T�C�Y
			HWND_DESKTOP,					// �e�E�B���h�E�Ȃ�
			(HMENU)NULL,					// ���j���[�Ȃ�
			_hInstance,						// �C���X�^���X�n���h��
			(LPVOID)NULL);					// �ǉ������Ȃ�

											// �E�C���h�E�T�C�Y���Čv�Z�iMetrics�����ł́A�t���[���f�U�C���ŃN���C�A���g�̈�T�C�Y���ς���Ă��܂��̂Łj
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
//�R���X�g���N�^
MainWindows::MainWindows(HINSTANCE 	hInstance) {
	//�E�B���h�E�T�C�Y�̑��
	m_width = SCREEN_X;
	m_height = SCREEN_Y;

	//�n���h���E�B���h�E�ݒ�
	InitWndClass(hInstance);

	//�E�B���h�E�̍쐬
	CreateMyWindow(hInstance);

}

MainWindows::~MainWindows() {
}

void MainWindows::ShowMyWindow(int _nWinMode) {
	// �E�C���h�E��\������
	ShowWindow(m_hwnd, _nWinMode);
	UpdateWindow(m_hwnd);
}

HWND MainWindows::GetHandolWindow() {
	return m_hwnd;
}

//WindowProcedure
LRESULT MainWindows::WndProc(HWND hwnd, 		// �E�B���h�E�n���h��
	UINT message,	// ���b�Z�[�W���ʎq
	WPARAM wParam,	// �t�я��P
	LPARAM lParam)	// �t�я��Q
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