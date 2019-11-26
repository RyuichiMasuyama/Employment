// ------------------------------------------------------------------------------
// 	DirectX11�������S����蒼���׋�
// ------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS

// ���������[�N���o�p
#define _CRTDBG_MAP_ALLOC

// C++�W��
#include <stdio.h>

// WinMain�����p
#include <Windows.h>

// WindowProcedure���܂ރN���X
#include "./Windows/WindowsManager.h"

// MyDirextX11�֌W�̃N���X
#include "./DirectX/DirectX11Manager.h"
#include "./DirectX/DirectXRenderManager.h"
#include "./Shader/Shader.h"
#include "./DirectX/SubResourceSendManager.h"

// Game�֌W�̃N���X
#include "./core/GameLoopManager.h"

// Scene�Ǘ��n�̃N���X
#include "./core/Scene/SceneManager.h"
#include "./TestScene.h"

#include <ImGui/ImGuiManager.h>

// -----------------------------------------------------------------------------
//  �����N���C�u�����̐ݒ�
// -----------------------------------------------------------------------------
#pragma comment(lib, "d3d11.lib")			// �����N�Ώۃ��C�u������d3d11.lib��ǉ�
#pragma comment(lib, "dxgi.lib")			// �����N�Ώۃ��C�u������dxgxi.lib��ǉ�
#pragma comment(lib, "D3DCompiler.lib")		// �����N�Ώۃ��C�u������d3dcompiler.lib��ǉ�
#pragma comment(lib, "winmm.lib")			// �����N�Ώۃ��C�u������winmm.lib��ǉ�

// -----------------------------------------------------------------------------
//  �v���g�^�C�v�錾
// -----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// WinMain
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	// ���b�Z�[�W�\����
//	MSG	msg;						
//
//	// ���������[�N�����m
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	 
//	//�E�C���h�E�̐����E������+
//	mslib::windows::MainWindows win(hInstance);
//
//	// DirectX������E�B���h�E�\��
//	win.ShowMyWindow(nCmdShow);
//
//	// DirectX11�̎g�p�E������
//	mslib::directx::DirectX11Manager& directx = mslib::directx::DirectX11Manager::GetInstance();
//	mslib::directx::DirectX11Manager::GetInstance().Init(win.GetHandolWindow(), false);
//
//	// ImGui�̃Z�b�g�A�b�v
//	ImGuiSetUp(win.GetHandolWindow(), directx.GetDevice().Get(), directx.GetDeviceContext().Get());
//
//	// �V�[���}�l�[�W���[�����E�V�[���̐���
//	static mslib::scene::SceneManager& sceneManager = mslib::scene::SceneManager::GetInstance();
//	mslib::scene::SceneManager::GetInstance().CreateScnen<mslib::scene::TestScene>();
//
//	// �Q�[�����[�v�̍쐬
//	mslib::GameLoop gameLoop;
//	gameLoop.Init();
//
//	while (true) {
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	{  // ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
//		// Windows�̏���
//			if (msg.message == WM_QUIT) {  // PostQuitMessage()���Ă΂�āAWM_QUIT���b�Z�[�W�������烋�[�v�I��
//				break;
//			} else {
//				// ���b�Z�[�W�̖|��Ƒ��o
//				TranslateMessage(&msg);
//				DispatchMessage(&msg);
//			}
//		} else {
//			gameLoop.Update();
//
//			gameLoop.Render();
//		}
//
//	}
//
//	gameLoop.Exit();
//
//	ImGuiCreanUp();
//
//	return (int)msg.wParam;
//}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���b�Z�[�W�\����
	MSG	msg;

	// ���������[�N�����m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//�E�C���h�E�̐����E������+
	mslib::windows::MainWindows win(hInstance);

	// DirectX������E1�B���h�E�\��
	win.ShowMyWindow(nCmdShow);

	mslib::directx::DirectX11Manager::GetInstance().Init(win.GetHandolWindow(), false);
	mslib::shader::ShaderLoader loader;
	mslib::directx::PixelShader aa;

	aa = loader.Load("shader/PSGauss.fx", mslib::shader::ShaderType::PS);
	getchar();

}

