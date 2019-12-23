#include "./Shader/Shader.h"
#include "./AssetManager/AssetManager.h"

#ifdef DIRECTX11
#include "./ShaderCompiler.h"
#endif

namespace mslib {
namespace directx {


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

}

namespace shader{
void Shaders::SetVertexShader(VertexShader _shader) {
	m_vertexShader = _shader;
}
void Shaders::SetPixelShader(PixelShader _shader)
{
}
}
}

