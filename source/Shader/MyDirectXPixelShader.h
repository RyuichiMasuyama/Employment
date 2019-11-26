#pragma once

#include "./DirectX/DirectX11Manager.h"

namespace mslib {
namespace shader {

class PixelShaderManager {
	friend class ShaderWark;
	friend class DirectXRenderWork;
private:
	std::unordered_map<std::string, mslib::directx::PixelShader> m_pixel_shader;

public:
	PixelShaderManager() = default;

	//シェーダーのコンパイル
	void CreateShader(const char * _map_name, const char * _file_name, const char * _main_function_name = "main");

	mslib::directx::PixelShader GetShader(std::string _map_name) { return m_pixel_shader[_map_name]; };
};

}
}