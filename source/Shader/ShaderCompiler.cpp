#include "./Shader/ShaderCompiler.h"
#include "./Shader.h"
#include <d3dcompiler.h>
#include <locale>

#include <any>

namespace mslib {
namespace directx {

HRESULT CompileShaderFromFile(const char * _file_name, LPCSTR _main_fanction_name, LPCSTR _shader_version, ID3DBlob ** _compile_shader)
{
	//�R���p�C���������������ۂ�
	HRESULT hr = S_OK;

	//wchar_t�ɕϊ����邽�߂̕ϐ�
	wchar_t file_name[SHADER_NAME_MAX];
	size_t	name_len = 0;

	//char ���� wchar_t�@�֕ϊ�
	setlocale(LC_ALL, "japanese");
	mbstowcs_s(&name_len, file_name, SHADER_NAME_MAX, _file_name, _TRUNCATE);

	DWORD shader_flag = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG)||defined(_DEBUG)
	shader_flag |= D3DCOMPILE_DEBUG;
#endif // defined(DEBUG)||defined(_DEBUG)/

	//�R���p�C���V�F�[�_�[(Error���o)
	ID3DBlob *blob_error = nullptr;

	//�V�F�[�_�[�̃R���p�C��
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
			MessageBox(
				NULL,
				(char*)blob_error->GetBufferPointer(), "ShaderCompileError", MB_OK);
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

	std::any myAny;

	switch (_shaderType)
	{
	case ShaderType::VS: {
		//�R���p�C���ς݃V�F�[�_�[
		ID3DBlob * blob = nullptr;
		directx::VertexShader shader;

		HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "vs_5_0", &blob);

		if (FAILED(hr)) {
			return nullptr;
		}

		//���_�V�F�[�_�[�𐶐�
		hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.GetAddressOf());
		if (FAILED(hr)) {
			MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);

			blob->Release();
			return nullptr;
		}

		return shader;
	}

	case ShaderType::IL: {
		//�R���p�C���ς݃V�F�[�_�[
		ID3DBlob * blob = nullptr;

		//���_���C�A�E�g
		std::vector<D3D11_INPUT_ELEMENT_DESC >element;
		directx::InputLayout shader;
	
		InputLayoutPick(INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, element);

		HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "vs_5_0", &blob);

		//���_�f�[�^��`����
		hr = device->CreateInputLayout(&element.at(0), static_cast<UINT>(element.size()), blob->GetBufferPointer(), blob->GetBufferSize(), shader.GetAddressOf());
		if (FAILED(hr)) {
			MessageBox(nullptr, "CreateInputLayer error", "error", MB_OK);

			blob->Release();
			return nullptr;
		}
		return shader;
	}
	case ShaderType::PS: {
		//�R���p�C���ς݃V�F�[�_�[
		ID3DBlob * blob = nullptr;
		directx::PixelShader shader;
		HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "ps_5_0", &blob);

		if (FAILED(hr)) {
			return nullptr;
		}

		//���_�V�F�[�_�[�𐶐�
		hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, shader.GetAddressOf());
		if (FAILED(hr)) {
			MessageBox(nullptr, "CreateVertexShader error", "error", MB_OK);

			blob->Release();
			return nullptr;
		}
		myAny = shader;
		return shader;
	}

	case ShaderType::GS: {
		//�R���p�C���ς݃V�F�[�_�[
		ID3DBlob * blob = nullptr;
		directx::GeometryShader shader;

		HRESULT hr = directx::CompileShaderFromFile(_shaderName.c_str(), "main", "gs_5_0", &blob);

		if (FAILED(hr)) {
			return nullptr;
		}

		//���_�V�F�[�_�[�𐶐�
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
}
}