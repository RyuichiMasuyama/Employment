#include "./DirectXRenderTerget.h"

#include "./Renderer/RenderObject.h"

#include "./Windows/WindowsDefineData.h"

namespace mslib {
namespace directx {

const math::Matrix ShadowMapDirectXRenderTerget::SHADOW_BIAS = math::Matrix(
	0.5f, 0.0f, 0.0f, 0.0f,
	0.0f, -0.5f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f);

DirectXRenderTerget::DirectXRenderTerget(render::RenderTergetType _renderTergetType) :
	render::RenderTerget(_renderTergetType) {};

DirectXRenderTerget::~DirectXRenderTerget() = default;

void DirectXRenderTerget::SetRenderTerget() {
	// directx::DirectX11Manager::GetInstance().GetDeviceContext()->PSSetShaderResources(_number + 1, 1, m_shaderResourceView.GetAddressOf());
	DirectX11Manager::GetInstance().GetDeviceContext()->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
}

void DirectXRenderTerget::SetShaderResouce(int _number) {
	DirectX11Manager::GetInstance().GetDeviceContext()->PSSetShaderResources(_number, 1, m_shaderResourceView.GetAddressOf());
}

void DirectXRenderTerget::BufferClear() {
	auto deviceContext = DirectX11Manager::GetInstance().GetDeviceContext();
	auto depth = DirectX11Manager::GetInstance().GetDepthStencilView();

	auto renderTergetView = m_renderTergetView;
	// auto renderTergetView = DirectX11Manager::GetInstance().GetRenderTargetView();

	deviceContext->OMSetRenderTargets(1, renderTergetView.GetAddressOf(), depth.Get());
	deviceContext->ClearRenderTargetView(renderTergetView.Get(), m_color);
	deviceContext->ClearDepthStencilView(depth.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	UniqueProcess();
}

render::CameraTexture DirectXRenderTerget::GetCameraTexture()
{
	return m_shaderResourceView;
}

std::weak_ptr<math::Matrix> DirectXRenderTerget::GetCameraPorjection()
{
	return render::RenderTerget::GetCameraProjection();
}

//void DirectXRenderTerget::Pipeline() {
//
//	//////////////////////////////////////////////////////////////////////
//	//					シェーダーセッティング部分						//
//	//////////////////////////////////////////////////////////////////////
//	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
//
//	//weak_ptr型でrender_objectを代入
//	// auto render_object = m_directx_render_object_warehouse->OutRenderObject(_render_command->m_render_model_name);
//
//	// if (render_object.expired())return;
//
//	//unipu_ptr型でシェーダリソースズを参照
//	auto material = Mesh()->GetMaterial();
//
//	//描画用のシェーダーやレイアウト、頂点データーを送信
//	// 頂点フォーマットをセット
//	auto il = ShaderWark::GetInstance().GetVertexShaderManager()->GetInputLayer(material->vsName.c_str());
//	m_device_context->IASetInputLayout(il.Get());
//
//	// 頂点シェーダーをセット
//	auto vs = ShaderWark::GetInstance().GetVertexShaderManager()->GetVertexShader(material->vsName.c_str());
//	m_device_context->VSSetShader(vs.Get(), nullptr, 0);
//
//	// ピクセルシェーダーをセット
//	auto ps = ShaderWark::GetInstance().GetPixelShaderManager()->GetShader(material->psName.c_str());
//	m_device_context->PSSetShader(ps.Get(), nullptr, 0);
//
//	// サンプラーステートを転送
//	// m_device_context->PSSetSamplers(0, 1, render_object.lock()->GetAddressOf());
//
//	//ジオメトリシェーダーをセット
//	auto gs = ShaderWark::GetInstance().GetGeometryShaderManager()->GetShader(material->gsName.c_str());
//	m_device_context->GSSetShader(gs.Get(), nullptr, 0);
//
//	//ハルシェーダーをセット
//	m_device_context->HSSetShader(nullptr, nullptr, 0);
//
//	//ドメインシェーダーをセット
//	m_device_context->DSSetShader(nullptr, nullptr, 0);
//
//	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
//
//	//////////////////////////////////////////////////////////////////////
//	//					頂点データーセッティング部分					//
//	//////////////////////////////////////////////////////////////////////
//	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
//
//	// 頂点バッファをセットする
//	unsigned int stride = sizeof(render::Vertex3DModel);
//	unsigned  offset = 0;
//
//	Transform::TransformSendContext::GetInstance().SendTransform(_render_command->m_matrix, Transform::TransformSendContext::TYPE::WORLD);
//
//	m_device_context->IASetVertexBuffers(0, 1, render_object.lock()->GetVertexBuffer().GetAddressOf(), &stride, &offset);
//
//	//インデックスバッファをセット
//	m_device_context->IASetIndexBuffer(render_object.lock()->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
//
//	for (unsigned int i = 0; i < material->textureName.size(); i++) {
//		m_device_context->PSSetShaderResources(i, 1, material->texture[i].GetAddressOf());
//	}
//	// m_device_context->PSSetShaderResources(1, 1, shader_resources->m_shadowMapshade.GetAddressOf());
//
//	// 描画！！！
//	m_device_context->DrawIndexed(
//		render_object.lock()->GetMesh()->GetPolygons()->index.size(),					// インデックスの数
//		0,							// 最初のインデックスバッファの位置
//		0							// 頂点バッファの最初からの位置
//	);
//
//}

MainDirectXRenderTerget::MainDirectXRenderTerget()
	:DirectXRenderTerget(render::RenderTergetType::MAIN) {
	m_color[0] = 0.f;
	m_color[1] = 0.f;
	m_color[2] = 1.f;
	m_color[3] = 1.f;

	// 2次元テクスチャの設定
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(texDesc));
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width = SCREEN_X;
	texDesc.Height = SCREEN_Y;
	texDesc.CPUAccessFlags = 0;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;

	// 2次元テクスチャの生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateTexture2D(
		&texDesc,
		NULL,
		m_texture2d.GetAddressOf());

	// レンダーターゲットビューの設定
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// レンダーターゲットビューの生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateRenderTargetView(
		m_texture2d.Get(),
		&rtvDesc,
		m_renderTergetView.GetAddressOf());

	// シェーダリソースビューの設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));
	srvDesc.Format = rtvDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	// シェーダリソースビューの生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateShaderResourceView(
		m_texture2d.Get(),
		&srvDesc,
		m_shaderResourceView.GetAddressOf());

	// サンプラステートの設定
	D3D11_SAMPLER_DESC smpDesc;
	memset(&smpDesc, 0, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	smpDesc.MinLOD = 0;
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// サンプラステート生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateSamplerState(
		&smpDesc,
		m_samplerState.GetAddressOf());
}

SubDirectXRenderTerget::SubDirectXRenderTerget()
	:DirectXRenderTerget(render::RenderTergetType::SUBCAMERA) {
	m_color[0] = 0.f;
	m_color[1] = 0.f;
	m_color[2] = 1.f;
	m_color[3] = 1.f;
	// 2次元テクスチャの設定
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(texDesc));
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width = SCREEN_X;
	texDesc.Height = SCREEN_Y;
	texDesc.CPUAccessFlags = 0;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;

	// 2次元テクスチャの生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateTexture2D(
		&texDesc,
		NULL,
		m_texture2d.GetAddressOf());

	// レンダーターゲットビューの設定
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// レンダーターゲットビューの生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateRenderTargetView(
		m_texture2d.Get(),
		&rtvDesc,
		m_renderTergetView.GetAddressOf());

	// シェーダリソースビューの設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));
	srvDesc.Format = rtvDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	// シェーダリソースビューの生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateShaderResourceView(
		m_texture2d.Get(),
		&srvDesc,
		m_shaderResourceView.GetAddressOf());

	// サンプラステートの設定
	D3D11_SAMPLER_DESC smpDesc;
	memset(&smpDesc, 0, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	smpDesc.MinLOD = 0;
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// サンプラステート生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateSamplerState(
		&smpDesc,
		m_samplerState.GetAddressOf());

}

ShadowMapDirectXRenderTerget::ShadowMapDirectXRenderTerget()
	:DirectXRenderTerget(render::RenderTergetType::SHADOW_MAP) {
	m_color[0] = 1.f;
	m_color[1] = 1.f;
	m_color[2] = 1.f;
	m_color[3] = 1.f;
	// 2次元テクスチャの設定
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(texDesc));
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width = SCREEN_X;
	texDesc.Height = SCREEN_Y;
	texDesc.CPUAccessFlags = 0;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;

	// 2次元テクスチャの生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateTexture2D(
		&texDesc,
		NULL,
		m_texture2d.GetAddressOf());

	// レンダーターゲットビューの設定
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// レンダーターゲットビューの生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateRenderTargetView(
		m_texture2d.Get(),
		&rtvDesc,
		m_renderTergetView.GetAddressOf());

	// シェーダリソースビューの設定
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));
	srvDesc.Format = rtvDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	// シェーダリソースビューの生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateShaderResourceView(
		m_texture2d.Get(),
		&srvDesc,
		m_shaderResourceView.GetAddressOf());

	// サンプラステートの設定
	D3D11_SAMPLER_DESC smpDesc;
	memset(&smpDesc, 0, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	smpDesc.BorderColor[0] = 1.0f;
	smpDesc.BorderColor[1] = 1.0f;
	smpDesc.BorderColor[2] = 1.0f;
	smpDesc.BorderColor[3] = 1.0f;
	smpDesc.MaxAnisotropy = 1;
	smpDesc.MipLODBias = 0;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
	smpDesc.MinLOD = D3D11_FTOI_INSTRUCTION_MIN_INPUT;
	smpDesc.MaxLOD = D3D11_FTOI_INSTRUCTION_MAX_INPUT;

	// サンプラステート生成
	directx::DirectX11Manager::GetInstance().GetDevice()->CreateSamplerState(
		&smpDesc,
		m_samplerState.GetAddressOf());

	shader::ShaderLoader shaderLoader;
	shaderLoader.Load("shader/psShadowMap.fx", m_ps, shader::ShaderType::PS);
	shaderLoader.Load("shader/vsShadowMap.fx", m_vs, shader::ShaderType::VS);
	shaderLoader.Load("shader/vsShadowMap.fx", m_il, shader::ShaderType::IL);
}

void ShadowMapDirectXRenderTerget::UniqueProcess() {
	//cbParam.Shadow = *DirectXRenderTerget::GetCameraPorjection().lock() * SHADOW_BIAS;
	auto deviceContext = DirectX11Manager::GetInstance().GetDeviceContext();

	deviceContext->IASetInputLayout(m_il.Get());
	deviceContext->PSSetShader(m_ps.Get(), nullptr, 0);
	deviceContext->VSSetShader(m_vs.Get(), nullptr, 0);
	deviceContext->GSSetShader(nullptr, nullptr, 0);
	deviceContext->HSSetShader(nullptr, nullptr, 0);
	deviceContext->DSSetShader(nullptr, nullptr, 0);
}

BasicDirectXRenderTerget::BasicDirectXRenderTerget() 
	:DirectXRenderTerget(render::RenderTergetType::BASIC) {
	m_color[0] = 0.f;
	m_color[1] = 0.f;
	m_color[2] = 1.f;
	m_color[3] = 1.f;
	auto& dxInce = DirectX11Manager::GetInstance();
	m_renderTergetView = dxInce.GetRenderTargetView();
	m_samplerState = dxInce.GetSamplerState();
	m_shaderResourceView = nullptr;
	m_texture2d= nullptr;

}

PostEffectDirectXRenderTerget::PostEffectDirectXRenderTerget()
	:DirectXRenderTerget(render::RenderTergetType::BASIC) {
	m_color[0] = 0.f;
	m_color[1] = 0.f;
	m_color[2] = 1.f;
	m_color[3] = 1.f;
}

}
}
