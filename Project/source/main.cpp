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
#include "./Renderer/DirectXRenderManager.h"
#include "./Shader/Shader.h"
#include "./MyDirectXTransform.h"
#include "./DirectX/DirectXTextureManager.h"

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
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���b�Z�[�W�\����
	MSG	msg;						

	// ���������[�N�����m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	 
	//�E�C���h�E�̐����E������+
	mslib::windows::MainWindows win(hInstance);

	// DirectX������E�B���h�E�\��
	win.ShowMyWindow(nCmdShow);

	// DirectX11�̎g�p�E������
	mslib::directx::DirectX11Manager& directx = mslib::directx::DirectX11Manager::GetInstance();
	mslib::directx::DirectX11Manager::GetInstance().Init(win.GetHandolWindow(), false);

	// ���f���q�ɂ̐���
	static mslib::render::DirectXRenderObjectWarehouse directx_render_object_warehouse;

	// �V�F�[�_�[�̐���
	static mslib::directx::ShaderWark shader_wark(mslib::directx::DirectX11Manager::GetInstance().GetDevice());

	// �e�N�X�`���̃��[�_�[
	static mslib::texture::TextureLoder texture_loader(mslib::directx::DirectX11Manager::GetInstance().GetDevice(),
		mslib::directx::DirectX11Manager::GetInstance().GetDeviceContext());

	// ���f�����[�_�[����
	static mslib::render::DirectXRenderObjectLoder directx_render_object_loder(directx.GetDevice(), &shader_wark, &directx_render_object_warehouse, &texture_loader);

	// �`��֌W�ŕK�v�ɂȂ�}�g���b�N�X�𑗂�N���X
	mslib::Transform::TransformSendContext& transform_send_context = mslib::Transform::TransformSendContext::GetInstance();

	transform_send_context.Init(directx.GetDevice(), directx.GetDeviceContext());

	// ImGui�̃Z�b�g�A�b�v
	ImGuiSetUp(win.GetHandolWindow(), directx.GetDevice().Get(), directx.GetDeviceContext().Get());

	// �����_�[
	mslib::render::DirectXRender& m_directx_render = mslib::render::DirectXRender::GetInstance();
	mslib::render::DirectXRender::GetInstance().Initialize(&directx, &directx_render_object_warehouse);

	// �Q�[�����[�v�̍쐬
	static Game::GameLoop game_loop(&directx);
	
	// �V�[���}�l�[�W���[����
	static mslib::scene::SceneManager& sceneManager = mslib::scene::SceneManager::GetInstance();

	shader_wark.Create(); 

	directx_render_object_loder.LoadRenderObjectTest();

	game_loop.Init();

	// �V�[���̐���
	mslib::scene::SceneManager::GetInstance().CreateScnen<mslib::scene::TestScene>();
	
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	{  // ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		// Windows�̏���
			if (msg.message == WM_QUIT) {  // PostQuitMessage()���Ă΂�āAWM_QUIT���b�Z�[�W�������烋�[�v�I��
				break;
			} else {
				// ���b�Z�[�W�̖|��Ƒ��o
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

