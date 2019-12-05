#include "./DirectXPipeline.h"
#include "./Renderer/RenderObject.h"
#include "./SubResourceSendManager.h"

namespace mslib {
namespace directx {

void DirectXPipeline::SetVertexPixcle(std::string _vs, std::string _ps) {
	shader::ShaderLoader shaderLoader;
	shaderLoader.Load(_vs, m_shaderResource.vertexShader, shader::ShaderType::VS);
	shaderLoader.Load(_ps, m_shaderResource.pixelShader, shader::ShaderType::PS);
	shaderLoader.Load(_vs, m_shaderResource.inputLayer, shader::ShaderType::IL);
}

void DirectXPipeline::SetGeometory(std::string _gs) {
	shader::ShaderLoader shaderLoader;
	shaderLoader.Load(_gs, m_shaderResource.geometryShader, shader::ShaderType::GS);
}

void DirectXPipeline::SetHullDomainShader(std::string _ds, std::string _hs) {
	shader::ShaderLoader shaderLoader;
	shaderLoader.Load(_ds, m_shaderResource.domainShader, shader::ShaderType::DS);
	shaderLoader.Load(_hs, m_shaderResource.hullShader, shader::ShaderType::HS);
}
void DirectXPipeline::SetTexture(texture::Texture _texture, int _setNumber) {
	if (_setNumber < m_texture.size()) m_texture[_setNumber] = _texture;
}

//
//// 位置情報
//directx::SubResourceSendManager::GetInstance().SetWorldObjectBuffer();
void DirectXPipeline::Draw() {
	auto deviceContext = DirectX11Manager::GetInstance().GetDeviceContext();

	//描画用のシェーダーやレイアウト、頂点データーを送信
	// 頂点フォーマットをセット
	deviceContext->IASetInputLayout(m_shaderResource.inputLayer.Get());

	// 頂点シェーダーをセット
	deviceContext->VSSetShader(m_shaderResource.vertexShader.Get(), nullptr, 0);

	// ピクセルシェーダーをセット
	deviceContext->PSSetShader(m_shaderResource.pixelShader.Get(), nullptr, 0);

	//// サンプラーステートを転送
	//deviceContext->PSSetSamplers(0, 1, .lock()->GetAddressOf());

	//ジオメトリシェーダーをセット
	deviceContext->GSSetShader(m_shaderResource.geometryShader.Get(), nullptr, 0);

	//ハルシェーダーをセット
	deviceContext->HSSetShader(m_shaderResource.hullShader.Get(), nullptr, 0);

	//ドメインシェーダーをセット
	deviceContext->DSSetShader(m_shaderResource.domainShader.Get(), nullptr, 0);

	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//////////////////////////////////////////////////////////////////////
	//					頂点データーセッティング部分					//
	//////////////////////////////////////////////////////////////////////
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	// 頂点バッファをセットする
	unsigned int stride = sizeof(render::Vertex3DModel);
	unsigned  offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, m_vertex_buffer.GetAddressOf(), &stride, &offset);

	//インデックスバッファをセット
	deviceContext->IASetIndexBuffer(m_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	auto material = m_mesh->GetMaterial();
	for (unsigned int i = 0; i < m_texture.size(); i++) {
		deviceContext->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}
	SubResourceSendManager::GetInstance().SetMaterialBuffer(material);

	unsigned int indexCount = static_cast<int>(m_mesh->GetPolygons()->index.size());
	// 描画！！！
	deviceContext->DrawIndexed(
		indexCount,					// インデックスの数
		0,							// 最初のインデックスバッファの位置
		0							// 頂点バッファの最初からの位置
	);
}

void DirectXPipeline::NoSetShaderDraw() {
	auto deviceContext = DirectX11Manager::GetInstance().GetDeviceContext();

	// 頂点バッファをセットする
	unsigned int stride = sizeof(render::Vertex3DModel);
	unsigned  offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, m_vertex_buffer.GetAddressOf(), &stride, &offset);

	//インデックスバッファをセット
	deviceContext->IASetIndexBuffer(m_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	auto material = m_mesh->GetMaterial();
	for (unsigned int i = 0; i < m_texture.size(); i++) {
		deviceContext->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}
	SubResourceSendManager::GetInstance().SetMaterialBuffer(material);

	unsigned int indexCount = static_cast<int>(m_mesh->GetPolygons()->index.size());
	// 描画！！！
	deviceContext->DrawIndexed(
		indexCount,					// インデックスの数
		0,							// 最初のインデックスバッファの位置
		0							// 頂点バッファの最初からの位置
	);
}

void DirectXPipeline::CreateVertexBuffer(size_t _vertexSize, size_t _vertexNum,void *_vertexFrontAddress) {
	HRESULT hr;

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;							// バッファ使用方法
	bd.ByteWidth = static_cast<UINT>(_vertexSize * _vertexNum);						// バッファの大きさ
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// 頂点バッファ
	bd.CPUAccessFlags = 0;									// CPUアクセス不要

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _vertexFrontAddress;							// バッファの初期値
	
	hr = DirectX11Manager::GetInstance().GetDevice()->
		CreateBuffer(&bd, &InitData, m_vertex_buffer.GetAddressOf());		// バッファ生成
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return;
	}

	return;
}

void DirectXPipeline::CreateIndexBuffer(size_t _indexNum, void* _indexFrontAddress) {
	// インデックスバッファ生成
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;								// バッファ使用方
	bd.ByteWidth = sizeof(unsigned int) * static_cast<UINT>(_indexNum);				// バッファの大き
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;						// インデックスバッファ
	bd.CPUAccessFlags = 0;										// CPUアクセス不要

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _indexFrontAddress;

	HRESULT hr = DirectX11Manager::GetInstance().GetDevice()->
		CreateBuffer(&bd, &InitData, m_index_buffer.GetAddressOf());
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(index buffer) error", "Error", MB_OK);
		return;
	}
}

void DirectXPipeline::LoadTexture(std::string _textureName) {
	if (!(_textureName == "null" || _textureName == " ")) {
		texture::TextureLoader loader;
		m_texture.push_back(loader.Load(_textureName));
	} else {
		m_texture.push_back(nullptr);
	}
}

}
}