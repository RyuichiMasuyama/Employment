#include "MyDirectXVertexShader.h"
#include "./Shader/Shader.h"

namespace mslib {
namespace shader {

//レイアウトとレイアウトサイズの取得
void VertexShaderManager::InputLayoutPick(
	INPUT_LAYOUT_NAME _input_layout_name, std::vector<D3D11_INPUT_ELEMENT_DESC>& element
)
{
	//std::vector<D3D11_INPUT_ELEMENT_DESC> element;

	//D3D11_INPUT_ELEMENT_DESC * element = new D3D11_INPUT_ELEMENT_DESC[3];

	//D3D11_INPUT_ELEMENT_DESC* element;
	switch (_input_layout_name)
	{
	case INPUT_LAYOUT_POS_COLOR:
		//D3D11_INPUT_ELEMENT_DESC _element = { "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		element.push_back({ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,		0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		//element[0] = { "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		//element[1] = { "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,		0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };

		//*_element = element;

		//_layout_num = 2;

		break;
	case INPUT_LAYOUT_POS_NORMAL:
		//*_element = new D3D11_INPUT_ELEMENT_DESC[2];
		element.push_back({ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });

		break;
	case INPUT_LAYOUT_POS_NORMAL_COLOR:
		//*_element = new D3D11_INPUT_ELEMENT_DESC[3]{
		element.push_back({ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		//};

		break;
	case INPUT_LAYOUT_POS_NORMAL_TEXCOORD:
		element.push_back({ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "NORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });

		//*_element = element;

		//_layout_num = 3;

		break;
		//case INPUT_LAYOUT_POS_NORMAL_TEXCOORD_COLOR:
		//	*_element = new D3D11_INPUT_ELEMENT_DESC[4]{
		//		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "COLOR",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		//	};

		//	break;
	case INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD:
		element.push_back({ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });


		break;
		//case INPUT_LAYOUT_POS_NORMAL_TANGENT_BINORMAL_TEXCOORD:
		//	*_element = new D3D11_INPUT_ELEMENT_DESC[5]{
		//		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "BINORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		//	};

		//	break;
		//case INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD_COLOR:
		//	*_element = new D3D11_INPUT_ELEMENT_DESC[5]{
		//		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "COLOR",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		//	};

		//	break;
		//case INPUT_LAYOUT_POS_NORMAL_TANGENT_BINORMAL_TEXCOORD_COLOR:
		//	*_element = new D3D11_INPUT_ELEMENT_DESC[6]{
		//		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "BINORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//		{ "COLOR",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		//	};

		//	break;
	case INPUT_LAYOUT_MAX:
		break;
	default:
		break;
	}

	//_layout_num = sizeof(_element) / sizeof(_element[0]);
}

void VertexShaderManager::CreateShader(INPUT_LAYOUT_NAME _input_layout_name, const char * _map_name, const char * _file_name, const char * _main_function_name)
{
	//コンパイル済みシェーダー
	ID3DBlob* blob = nullptr;

	//頂点レイアウト
	std::vector<D3D11_INPUT_ELEMENT_DESC >element;
	//unsigned int element_num;

	InputLayoutPick(_input_layout_name, element);

	HRESULT hr = directx::CompileShaderFromFile(_file_name, _main_function_name, "vs_5_0", &blob);

	if (FAILED(hr)) {
		return;
	}

	//頂点シェーダーを生成
	hr = m_device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_vertex_shader[_map_name].GetAddressOf());
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);

		blob->Release();
		return;
	}

	//頂点データ定義生成
	hr = m_device->CreateInputLayout(&element.at(0), element.size(), blob->GetBufferPointer(), blob->GetBufferSize(), m_input_layout[_map_name].GetAddressOf());
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateInputLayer error", "error", MB_OK);

		blob->Release();
		return;
	}

	//if (element != nullptr) {
	//	delete element;
	//}

	return;

}

mslib::directx::VertexShader VertexShaderManager::GetVertexShader(const char * _map_name)
{
	return m_vertex_shader[_map_name];
}

mslib::directx::InputLayout VertexShaderManager::GetInputLayer(const char * _map_name)
{
	return m_input_layout[_map_name];
}

}
}