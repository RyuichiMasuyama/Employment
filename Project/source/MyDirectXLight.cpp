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

	//コンスタントバッファ4をｂ6レジスタへセット（頂点シェーダー用）
	m_device_context->VSSetConstantBuffers(4, 1, buff.GetAddressOf());
	//コンスタントバッファ4をｂ6レジスタへセット(ピクセルシェーダー用)
	m_device_context->PSSetConstantBuffers(4, 1, buff.GetAddressOf());

}

}
}