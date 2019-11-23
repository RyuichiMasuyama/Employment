#pragma once

#pragma comment (lib,"winmm.lib")

#include <Windows.h>
#include <mmsystem.h>
#include <memory>

#include "./DirectX/DirectX11Manager.h"
#include "MyDirectXMath.h"

class FpsManager {
private:
	struct ConstantBufferTime {
		math::Vector4 time;
		math::Vector4 delta_time;
	};

	//�R���X�^���g�o�b�t�@
	mslib::directx::ConstantBuffer m_constant_buffer;

	//�f�o�C�X
	mslib::directx::Device m_device;

	//�f�o�C�X�R���e�L�X�g
	mslib::directx::DeviceContext m_device_context;

	LARGE_INTEGER m_counter;
	LONGLONG m_old_counter;
	LONGLONG m_start_timer;
	LONGLONG m_end_timer;

	double m_freq;

	bool m_fixed_flag;

	//�Œ�t���[���̕���
	double m_fixed_time_fraction;
	
	//�Œ�t���[���̕ꐔ
	double m_fixed_time_parameter;

	//�σt���[���ɂ�����A�v���N������̌o�ߎ���
	float m_time;

	//�σt���[���ɂ����鎞�Ԃ̌o��
	float m_delta_time;

	//FPS�v�Z�n�̃A�b�v�f�[�g
	void FpsUpdate();

	//�R���X�^���g�o�b�t�@���M�p�A�b�v�f�[�g
	void SendConstantBufferUpdate();

public:// bar.h
	//FpsManager & operator=(const FpsManager& bar) = default;  // <- �܂�cpp���œK�؂Ɏ������Ă��K�v������
	FpsManager(mslib::directx::DirectX11Manager*_directx);

	~FpsManager(); // �f�X�g���N�^���C�����C����;

	void Update();

	//�Œ�t���[���̃t���O
	bool GetFixedFlag() { return m_fixed_flag; }

	float GetDeltaTime() { return m_delta_time; };
};