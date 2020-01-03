#pragma once

#pragma comment (lib,"winmm.lib")

#include <Windows.h>
#include <mmsystem.h>
#include <Singleton.h>
#include <memory>

#ifdef DIRECTX11
#include "MyDirectXMath.h"
#endif

namespace mslib {

class FpsManager :public pattern::Singleton<FpsManager> {
private:
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

public:
	FpsManager();

	~FpsManager() = default; // �f�X�g���N�^���C�����C����;

	void Update();

	//�Œ�t���[���̃t���O
	bool GetFixedFlag() { return m_fixed_flag; }

	float GetDeltaTime() { return m_delta_time; };
};

}