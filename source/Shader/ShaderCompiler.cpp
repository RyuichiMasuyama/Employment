#include "./Shader/ShaderCompiler.h"
#include "./Shader.h"
#include <d3dcompiler.h>
#include <locale>

#include <any>

namespace mslib {
namespace directx {

HRESULT CompileShaderFromFile(const char * _file_name, LPCSTR _main_fanction_name, LPCSTR _shader_version, ID3DBlob ** _compile_shader)
{
	//コンパイルが成功したか否か
	HRESULT hr = S_OK;

	//wchar_tに変換するための変数
	wchar_t file_name[SHADER_NAME_MAX];
	size_t	name_len = 0;

	//char から wchar_t　へ変換
	setlocale(LC_ALL, "japanese");
	mbstowcs_s(&name_len, file_name, SHADER_NAME_MAX, _file_name, _TRUNCATE);

	DWORD shader_flag = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG)||defined(_DEBUG)
	shader_flag |= D3DCOMPILE_DEBUG;
#endif // defined(DEBUG)||defined(_DEBUG)/

	//コンパイルシェーダー(Error検出)
	ID3DBlob *blob_error = nullptr;

	//シェーダーのコンパイル
	hr = D3DCompileFromFile(
		file_name,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_main_fanction_name,
		_shader_version,
		shader_flag,
		0,
		_compile_shader,
		&blob_error
	);

	if (FAILED(hr)) {

		if (blob_error != nullptr) {
			MessageBox(NULL, (char*)blob_error->GetBufferPointer(), "ShaderCompileError", MB_OK);
		}
		if (blob_error) {
			blob_error->Release();
		}
		return hr;
	}

	return S_OK;

}
assets::AssetBase ShaderCompiler::Load(std::string _shaderName, ShaderType _shaderType) {
	auto device = directx::DirectX11Manager::GetInstance().GetDevice();

	switch (_shaderType)
	{
	case ShaderType::VS: {
		//コンパイル済みシェーダー
		ID3DBlob * blob = nullptr;
		directx::VertexShader shader;

		HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "vs_5_0", &blob);

		if (FAILED(hr)) {
			std::string errorMessage = "[" + _shaderName + "]is NotFound\nPlease check File path";
			MessageBox(nullptr, errorMessage.c_str(), "error", MB_OK);
			return nullptr;
		}

		//頂点シェーダーを生成
		hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.GetAddressOf());
		if (FAILED(hr)) {
			MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);

			blob->Release();
			return nullptr;
		}

		return shader;
	}

	case ShaderType::IL: {
		//コンパイル済みシェーダー
		ID3DBlob * blob = nullptr;

		//頂点レイアウト
		std::vector<D3D11_INPUT_ELEMENT_DESC >element;
		directx::InputLayout shader;
	
		InputLayoutPick(INPUT_LAYOUT_POS_NORMAL_TEXCOORD, element);

		HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "vs_5_0", &blob);

		//頂点データ定義生成
		hr = device->CreateInputLayout(&element.at(0), static_cast<UINT>(element.size()), blob->GetBufferPointer(), blob->GetBufferSize(), shader.GetAddressOf());
		if (FAILED(hr)) {
			MessageBox(nullptr, "CreateInputLayer error", "error", MB_OK);

			blob->Release();
			return nullptr;
		}
		return shader;
	}
	case ShaderType::PS: {
		//コンパイル済みシェーダー
		ID3DBlob * blob = nullptr;
		directx::PixelShader shader;
		HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "ps_5_0", &blob);

		if (FAILED(hr)) {
			std::string errorMessage = "[" + _shaderName + "]is NotFound\nPlease check File path";
			MessageBox(nullptr, errorMessage.c_str(), "error", MB_OK);
			return nullptr;
		}

		//頂点シェーダーを生成
		hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.GetAddressOf());
		if (FAILED(hr)) {
			MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);

			blob->Release();
			return nullptr;
		}
		return shader;
	}

	case ShaderType::GS: {
		//コンパイル済みシェーダー
		ID3DBlob * blob = nullptr;
		directx::GeometryShader shader;

		HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "gs_5_0", &blob);

		if (FAILED(hr)) {
			std::string errorMessage = "[" + _shaderName + "]is NotFound\nPlease check File path";
			MessageBox(nullptr, errorMessage.c_str(), "error", MB_OK);
			return nullptr;
		}

		//頂点シェーダーを生成
		hr = device->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.GetAddressOf());
		if (FAILED(hr)) {
			MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);

			blob->Release();
			return nullptr;
		}

		return shader;
	}
	default:
		return nullptr;
		break;
	}
	return nullptr;
}

directx::PixelShader ShaderCompiler::PSLoad(std::string _shaderName) {
	auto device = directx::DirectX11Manager::GetInstance().GetDevice();
	//コンパイル済みシェーダー
	ID3DBlob * blob = nullptr;
	directx::PixelShader shader;
	HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "ps_5_0", &blob);

	if (FAILED(hr)) {
		std::string errorMessage = "[" + _shaderName + "]is NotFound\nPlease check File path";
		MessageBox(nullptr, errorMessage.c_str(), "error", MB_OK);
		return nullptr;
	}

	//頂点シェーダーを生成
	hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.GetAddressOf());
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);

		blob->Release();
		return nullptr;
	}
	return shader;
}

directx::VertexShader ShaderCompiler::VSLoad(std::string _shaderName) {
	//コンパイル済みシェーダー
	auto device = directx::DirectX11Manager::GetInstance().GetDevice();
	ID3DBlob * blob = nullptr;
	directx::VertexShader shader;

	HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "vs_5_0", &blob);

	if (FAILED(hr)) {
		std::string errorMessage = "[" + _shaderName + "]is NotFound\nPlease check File path";
		MessageBox(nullptr, errorMessage.c_str(), "error", MB_OK);
		return nullptr;
	}

	//頂点シェーダーを生成
	hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.GetAddressOf());
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);

		blob->Release();
		return nullptr;
	}

	return shader;
}

directx::InputLayout ShaderCompiler::ILLoad(std::string _shaderName) {
	//コンパイル済みシェーダー
	auto device = directx::DirectX11Manager::GetInstance().GetDevice();
	ID3DBlob * blob = nullptr;

	//頂点レイアウト
	std::vector<D3D11_INPUT_ELEMENT_DESC >element;
	directx::InputLayout shader;

	InputLayoutPick(INPUT_LAYOUT_POS_NORMAL_TEXCOORD, element);

	HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "vs_5_0", &blob);

	if (FAILED(hr)) {
		return nullptr;
	}

	//頂点データ定義生成
	hr = device->CreateInputLayout(&element.at(0), static_cast<UINT>(element.size()), blob->GetBufferPointer(), blob->GetBufferSize(), shader.GetAddressOf());
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateInputLayout error", "error", MB_OK);

		blob->Release();
		return nullptr;
	}
	return shader;
}

directx::GeometryShader ShaderCompiler::GSLoad(std::string _shaderName) {
	auto device = directx::DirectX11Manager::GetInstance().GetDevice();
	//コンパイル済みシェーダー
	ID3DBlob * blob = nullptr;
	directx::GeometryShader shader;

	HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "gs_5_0", &blob);

	if (FAILED(hr)) {
		return nullptr;
	}

	//頂点シェーダーを生成
	hr = device->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.GetAddressOf());
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);

		blob->Release();
		return nullptr;
	}

	return shader;
}

directx::HullShader ShaderCompiler::HSLoad(std::string _shaderName) {
	auto device = directx::DirectX11Manager::GetInstance().GetDevice();
	return directx::HullShader();
}

directx::DomainShader ShaderCompiler::DSLoad(std::string _shaderName) {
	auto device = directx::DirectX11Manager::GetInstance().GetDevice();
	return directx::DomainShader();
}

void ShaderCompiler::InputLayoutPick(INPUT_LAYOUT_NAME _input_layout_name, std::vector<D3D11_INPUT_ELEMENT_DESC>& element)

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
		element.push_back({ "POSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "NORMAL",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });

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
	case INPUT_LAYOUT_POS_NORMAL_TEXCOORD_COLOR_TANGENT_BONEINDEX_BONEWIGHT_BONENUM:
		element.push_back({ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,	    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "BONEINDEX",	0, DXGI_FORMAT_R32G32B32A32_SINT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "BONEWIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		element.push_back({ "BONENUM",		0, DXGI_FORMAT_R32_SINT,			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });

		break;
	case INPUT_LAYOUT_MAX:
		break;
	default:
		break;
	}

	//_layout_num = sizeof(_element) / sizeof(_element[0]);
}
}
}