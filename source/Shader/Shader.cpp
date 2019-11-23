#include "./Shader/Shader.h"

namespace mslib {
namespace directx {

HRESULT CompileShaderFromFile(const char * _file_name, LPCSTR _main_fanction_name, LPCSTR _shader_version, ID3DBlob ** _compile_shader)
{
	//コンパイルが成功したか否か
	HRESULT hr = S_OK;

	//wchar_tに変換するための変数
	wchar_t file_name[SHADER_NAME_MAX];
	UINT	name_len = 0;

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

ID3D11Buffer* BufferCreater::CreateConstantBuffer(UINT _byte_size)
{
	// コンスタントバッファ生成用デスク
	D3D11_BUFFER_DESC bd;

	//コンスタントバッファ
	ID3D11Buffer* buffer;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;								// バッファ使用方法
	bd.ByteWidth = _byte_size;									// バッファの大き
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;					// コンスタントバッファ
	bd.CPUAccessFlags = 0;										// CPUアクセス不要

	HRESULT hr = m_device->CreateBuffer(&bd, nullptr, &buffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(constant buffer) error", "Error", MB_OK);
		return nullptr;
	}

	return buffer;
}

ID3D11Buffer * BufferCreater::CreateIndexBuffer(UINT* _index, UINT _index_num)
{
	//インデックスバッファ作成
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth = sizeof(UINT) * _index_num;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subresource_data;
	ZeroMemory(&subresource_data, sizeof(subresource_data));
	subresource_data.pSysMem = _index;

	ID3D11Buffer* buffer;
	if (FAILED(m_device->CreateBuffer(&buffer_desc, &subresource_data, &buffer))) {
		return nullptr;
	}
	return buffer;
}

//各種シェーダーの生成
void ShaderWark::Create() {
	//バーテックスシェーダー
	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "normal_vs", "shader/testvs.fx");
	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "2d_vs", "shader/vs2d.fx");
	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "gauss_vs", "shader/VSGauss.fx");

	//ピクセルシェーダー
	m_pixel_manager.CreateShader("normal_ps", "shader/pstest.fx");
	m_pixel_manager.CreateShader("2d_ps", "shader/ps2d.fx");
	m_pixel_manager.CreateShader("gauss_ps", "shader/PSGauss.fx");

	//ジオメトリシェーダー
	m_geometry_manager.CreateShader("normal_gs", "shader/Geometry/gs.fx");

	// ポストエフェクトシェーダー
	// Gauss
	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "Gauss", "shader/VSGauss.fx");
	m_pixel_manager.CreateShader("Gauss", "shader/PSGauss.fx");

	// Bloom

}

}
}
