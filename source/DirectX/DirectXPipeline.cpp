#include "./DirectXPipeline.h"
#include "./Renderer/RenderObject.h"
#include "./SubResourceSendManager.h"

namespace mslib {
namespace directx {

void DirectXPipeline::SetVertexPixcle(std::string _vs, std::string _ps) {
	shader::ShaderLoader shaderLoader;
	m_shaderResource.vertexShader = shaderLoader.Load(_vs, shader::ShaderType::VS);
	m_shaderResource.pixelShader = shaderLoader.Load(_ps, shader::ShaderType::PS);
	m_shaderResource.inputLayer = shaderLoader.Load(_ps, shader::ShaderType::IL);
}

void DirectXPipeline::SetGeometory(std::string _gs) {
	shader::ShaderLoader shaderLoader;
	m_shaderResource.geometryShader = shaderLoader.Load(_gs, shader::ShaderType::GS);
}

void DirectXPipeline::SetHullDomainShader(std::string _ds, std::string _hs) {
	shader::ShaderLoader shaderLoader;
	m_shaderResource.domainShader = shaderLoader.Load(_ds, shader::ShaderType::DS);
	m_shaderResource.hullShader = shaderLoader.Load(_hs, shader::ShaderType::HS);
}
//
//// 位置情報
//directx::SubResourceSendManager::GetInstance().SetWorldObjectBuffer();
void DirectXPipeline::Draw() {
	auto deviceContext = DirectX11Manager::GetInstance().GetDeviceContext();

	//描画用のシェーダーやレイアウト、頂点データーを送信
	// 頂点フォーマットをセット
	directx::VertexShader vs;
	directx::PixelShader ps;
	directx::InputLayout layer;
	directx::GeometryShader gs;
	directx::HullShader hs;
	directx::DomainShader ds;
/*
	m_shaderResource.vertexShader .As(&vs);
	m_shaderResource.pixelShader.As(&ps);
	m_shaderResource.inputLayer.As(&layer);
	m_shaderResource.geometryShader.As(&gs);
	m_shaderResource.hullShader.As(&hs);
	m_shaderResource.domainShader.As(&ds);
*/
	deviceContext->IASetInputLayout(layer.Get());

	// 頂点シェーダーをセット
	deviceContext->VSSetShader(vs.Get(), nullptr, 0);

	// ピクセルシェーダーをセット
	deviceContext->PSSetShader(ps.Get(), nullptr, 0);

	// サンプラーステートを転送
	// deviceContext->PSSetSamplers(0, 1, render_object.lock()->GetAddressOf());

	//ジオメトリシェーダーをセット
	deviceContext->GSSetShader(gs.Get(), nullptr, 0);

	//ハルシェーダーをセット
	deviceContext->HSSetShader(hs.Get(), nullptr, 0);

	//ドメインシェーダーをセット
	deviceContext->DSSetShader(ds.Get(), nullptr, 0);

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
		ShaderTexture tex;
		//m_texture[i].As(&tex);
		deviceContext->PSSetShaderResources(i, 1, tex.GetAddressOf());
	}

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
	texture::TextureLoader loader;
	m_texture.push_back(loader.Load(_textureName));
}

}
}