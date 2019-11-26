#pragma once

#include "DirectX/DirectX11Manager.h"
#include <list>
#include <unordered_map>
#include <string>

namespace mslib {
namespace  shader{

enum INPUT_LAYOUT_NAME :unsigned int {
	INPUT_LAYOUT_POS_NORMAL,
	INPUT_LAYOUT_POS_COLOR,
	INPUT_LAYOUT_POS_NORMAL_COLOR,
	INPUT_LAYOUT_POS_NORMAL_TEXCOORD,
	INPUT_LAYOUT_POS_NORMAL_TEXCOORD_COLOR,
	INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD,
	INPUT_LAYOUT_POS_NORMAL_TANGENT_BINORMAL_TEXCOORD,
	INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD_COLOR,
	INPUT_LAYOUT_POS_NORMAL_TANGENT_BINORMAL_TEXCOORD_COLOR,
	INPUT_LAYOUT_MAX
};


//VertexManagerƒNƒ‰ƒX
class VertexShaderManager {
	friend class ShaderWark;
	friend class DirectXRenderWork;
private:
	std::unordered_map<std::string, mslib::directx::VertexShader> m_vertex_shader;
	std::unordered_map<std::string, mslib::directx::InputLayout> m_input_layout;

	void InputLayoutPick(INPUT_LAYOUT_NAME _input_layout_name, std::vector<D3D11_INPUT_ELEMENT_DESC>& element);

public:
	VertexShaderManager() = default;

	void CreateShader(INPUT_LAYOUT_NAME _input_layout_name, const char * _map_name, const char* _file_name, const char* _main_function_name = "main");

	directx::VertexShader GetVertexShader(const char * _map_name);
	directx::InputLayout GetInputLayer(const char * _map_name);

};
}
}