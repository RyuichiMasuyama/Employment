#include "./FpsManager.h"
#include "./DirectX/SubResourceSendManager.h"

namespace mslib {

void FpsManager::FpsUpdate() {
	//�O��̎��Ԃ��擾
	m_old_counter = m_counter.QuadPart;

	//���݂̎��Ԃ��擾
	QueryPerformanceCounter(&m_counter);

	//�o�ߎ��Ԃ̎擾
	m_delta_time = static_cast<const float>((m_counter.QuadPart - m_old_counter) / m_freq);

	//�o�ߎ��Ԃ����Z
	m_fixed_time_fraction += m_delta_time;
	m_time += m_delta_time;

	//60FPS���K��
	m_fixed_flag = m_fixed_time_fraction > 1.0 / m_fixed_time_parameter;
	if (m_fixed_flag) {
		m_fixed_time_fraction = 0.0;
	}
}

FpsManager::FpsManager() {
	QueryPerformanceCounter(&m_counter);

	m_old_counter = m_counter.QuadPart;		//�������̎���(�N���b�N��)���擾

	LARGE_INTEGER frep;
	QueryPerformanceFrequency(&frep);		//	1�b������N���b�N�����擾
	m_freq = (double)frep.QuadPart;

	//�^�C�}�[�̏������Ԑݒ�
	m_start_timer = m_end_timer = 0;

	//�Œ�t���[�����[���̕����ݒ�
	m_fixed_time_fraction = 0.0;

	//�Œ�t���[�����[�g�̕ꐔ�ݒ�
	m_fixed_time_parameter = 60.0;
}

void FpsManager::Update() {

	//FPS�A�b�v�f�[�g
	FpsUpdate();

	if (GetFixedFlag()) {
		directx::SubResourceSendManager::GetInstance().SetTimeBuffer(
			math::Vector4(m_time, m_time / 2.f, m_time / 4.f, m_time / 8.f),
			math::Vector4(m_delta_time, m_delta_time / 2.f, m_delta_time / 4.f, m_delta_time / 8.f)
		);
	}
}

}