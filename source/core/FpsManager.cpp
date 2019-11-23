#include "FpsManager.h"
#include "./Shader/Shader.h"

void FpsManager::FpsUpdate(){
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

void FpsManager::SendConstantBufferUpdate(){
 
	ConstantBufferTime constant_buffer_time;

	constant_buffer_time.time.x = m_time;
	constant_buffer_time.time.y = m_time / 2.f;
	constant_buffer_time.time.z = m_time / 4.f;
	constant_buffer_time.time.w = m_time / 8.f;

	constant_buffer_time.delta_time.x = m_delta_time;
	constant_buffer_time.delta_time.y = m_delta_time / 2.f;
	constant_buffer_time.delta_time.z = m_delta_time / 4.f;
	constant_buffer_time.delta_time.w = m_delta_time / 8.f;

	//m_device_context->UpdateSubresource(
	//	m_constant_buffer.Get(),
	//	0,
	//	nullptr,
	//	&constant_buffer_time,
	//	0, 0);

	// �R���X�^���g�o�b�t�@4����3���W�X�^�փZ�b�g�i���_�V�F�[�_�[�p�j
	//m_device_context->VSSetConstantBuffers(5, 1, m_constant_buffer.GetAddressOf());
	// �R���X�^���g�o�b�t�@4����3���W�X�^�փZ�b�g(�s�N�Z���V�F�[�_�[�p)
	//m_device_context->PSSetConstantBuffers(5, 1, m_constant_buffer.GetAddressOf());
}

FpsManager::FpsManager(mslib::directx::DirectX11Manager * _directx):m_device(_directx->GetDevice()),m_device_context(_directx->GetDeviceContext())
{
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

	//�o�b�t�@�N���G�C�^�[
	//std::unique_ptr< MyDirectX11::Shader::BufferCreater > m_buffer_creater;
	mslib::directx::BufferCreater buffer_creater(_directx->GetDevice());
	//m_buffer_creater = std::make_unique < MyDirectX11::Shader::BufferCreater >(_directx->GetDevice());

	m_constant_buffer = buffer_creater.CreateConstantBuffer(sizeof(ConstantBufferTime));
}

FpsManager::~FpsManager() = default;

void FpsManager::Update() {
	
	//FPS�A�b�v�f�[�g
	FpsUpdate();

	//�R���X�^���g�o�b�t�@���M
	SendConstantBufferUpdate();
}