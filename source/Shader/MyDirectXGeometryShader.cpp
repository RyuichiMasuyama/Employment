#include "./Shader/Shader.h"
#include "MyDirectXGeometryShader.h"

namespace mslib {
namespace shader {

void GeometryShaderManager::CreateShader(const char * _map_name, const char * _file_name, const char * _main_function_name) {
	ID3DBlob* blob = nullptr;

	//ƒRƒ“ƒpƒCƒ‹
	HRESULT hr = directx::CompileShaderFromFile(_file_name, _main_function_name, "gs_5_0", &blob);
	if (FAILED(hr)) {
		return;
	}

	hr = directx::DirectX11Manager::GetInstance().GetDevice->
		CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_geometry_shader[_map_name].GetAddressOf());
	if (FAILED(hr)) {
		return;
	}

	return;
}
}
}