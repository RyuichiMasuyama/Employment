#include "MyDirectXLight.h"

#include "./Shader/Shader.h"

namespace mslib {
namespace Light {
ParallelLight::ParallelLight(mslib::directx::Device _device, mslib::directx::DeviceContext _device_context)
{
	m_device_context = _device_context;

	directx::BufferCreater creater(_device);

	buff = creater.CreateConstantBuffer(sizeof(ParalleLightConstantBuffer));
}

void ParallelLight::Update()
{

	ParalleLightConstantBuffer light_buff;

	light_buff.way = m_way;

	m_device_context->UpdateSubresource(buff.Get(),
		0,
		nullptr,
		&light_buff,
		0, 0);

	//�R���X�^���g�o�b�t�@4����6���W�X�^�փZ�b�g�i���_�V�F�[�_�[�p�j
	m_device_context->VSSetConstantBuffers(4, 1, buff.GetAddressOf());
	//�R���X�^���g�o�b�t�@4����6���W�X�^�փZ�b�g(�s�N�Z���V�F�[�_�[�p)
	m_device_context->PSSetConstantBuffers(4, 1, buff.GetAddressOf());

}

}
}