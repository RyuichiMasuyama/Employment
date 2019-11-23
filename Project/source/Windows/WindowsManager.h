#pragma once

//�E�B���h�E�쐬�̂���
#include <Windows.h>

//�W��
#include <stdio.h>
#include <stdlib.h>

namespace mslib {
namespace windows {

#define		FULLSCREEN		0				// �t���X�N���[���t���O

	class MainWindows {
	private:
		HWND			m_hwnd;						// �E�C���h�E�n���h��
		MSG				m_msg;						// ���b�Z�[�W�\����
		WNDCLASSEX		m_wcex;						// �E�C���h�E�N���X�\����

		int				m_width;					// �E�C���h�E�̕� �v�Z�p���[�N
		int				m_height;					// �E�C���h�E�̍��� �v�Z�p���[�N

		bool InitWndClass(HINSTANCE hInstance);		//�E�B���h�E�N���X�̍\���̐���

		bool CreateMyWindow(HINSTANCE _hInstance);	//�N���G�C�g�E�B���h�E���g��

	public:
		MainWindows(HINSTANCE 	hInstance);			//�R���X�g���N�^
		~MainWindows();								//�f�X�g���N�^

		void ShowMyWindow(int nWinMode);

		HWND GetHandolWindow();
		
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);			// �E�C���h�E�v���V�[�W��

	};
}
}