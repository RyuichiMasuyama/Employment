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
void Shaders::Send() {
	auto deviceContext = directx::DirectX11Manager::GetInstance().GetDeviceContext();

	//描画用のシェーダーやレイアウト、頂点データーを送信
	// 頂点フォーマットをセット
	deviceContext->IASetInputLayout(m_inputLayout.Get());

	// 頂点シェーダーをセット
	deviceContext->VSSetShader(m_vertexShader.Get(), nullptr, 0);

	// ピクセルシェーダーをセット
	deviceContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//// サンプラーステートを転送
	//deviceContext->PSSetSamplers(0, 1, .lock()->GetAddressOf());

	//ジオメトリシェーダーをセット
	deviceContext->GSSetShader(m_geometryShader.Get(), nullptr, 0);

	//ハルシェーダーをセット
	deviceContext->HSSetShader(m_hullShader.Get(), nullptr, 0);

	//ドメインシェーダーをセット
	deviceContext->DSSetShader(m_domainShader.Get(), nullptr, 0);
}
void Shaders::SetVertexShader(VertexShader _shader) {
	m_vertexShader = _shader;
}
void Shaders::SetPixelShader(PixelShader _shader) {
	m_pixelShader = _shader;
}
void Shaders::SetGeometryShader(GeometryShader _shader) {
	m_geometryShader = _shader;
}
void Shaders::SetDomainShader(DomainShader _shader) {
	m_domainShader = _shader;
}
void Shaders::SetHullShader(HullShader _shader) {
	m_hullShader = _shader;
}
void Shaders::SetInputLayout(InputLayer _inputLayout) {
	m_inputLayout = _inputLayout;
}
}
}

