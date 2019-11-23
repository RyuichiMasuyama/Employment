#include "./Shader/Shader.h"
#include "MyDirectXPixelShader.h"

namespace mslib{
namespace shader {

void PixelShaderManager::CreateShader(const char * _map_name, const char * _file_name, const char * _main_function_name)
{
	ID3DBlob* blob = nullptr;

	//ƒRƒ“ƒpƒCƒ‹
	HRESULT hr = directx::CompileShaderFromFile(_file_name, _main_function_name, "ps_5_0", &blob);
	if (FAILED(hr)) {
		return;
	}

	hr = m_device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pixel_shader[_map_name].GetAddressOf());
	if (FAILED(hr)) {
		return;
	}

	return;
}

}
}
