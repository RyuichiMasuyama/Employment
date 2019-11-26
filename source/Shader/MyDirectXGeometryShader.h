#pragma once

#include "./DirectX/DirectX11Manager.h"


namespace mslib {
namespace shader {

class GeometryShaderManager {
	friend class ShaderWark;
private:
	std::unordered_map<std::string, mslib::directx::GeometryShader> m_geometry_shader;

public:
	GeometryShaderManager() = default;

	//シェーダーのコンパイル
	void CreateShader(const char * _map_name, const char * _file_name, const char * _main_function_name = "main");

	mslib::directx::GeometryShader GetShader(std::string _map_name) { return m_geometry_shader[_map_name]; };
};
}
}