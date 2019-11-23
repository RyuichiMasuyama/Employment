#include "./RenderTerget.h"
#include "./Windows/WindowsDefineData.h"
#include "./MyDirectXTransform.h"

namespace mslib {
namespace render {

SubCameraRender::SubCameraRender() {
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
	m_device->CreateTexture2D(
		&texDesc,
		NULL,
		m_texture2d.GetAddressOf());

	// レンダーターゲットビューの設定
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// レンダーターゲットビューの生成
	m_device->CreateRenderTargetView(
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
	m_device->CreateShaderResourceView(
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
	m_device->CreateSamplerState(
		&smpDesc,
		m_samplerState.GetAddressOf());
}

std::weak_ptr<RenderTerget> RenderTergetManager::CreateRenderTerget(const RenderTergetType _renderType) {
	std::shared_ptr<RenderTerget> instance;

	switch (_renderType){
	case RenderTergetType::NORMAL:

		break;
	case RenderTergetType::SUBCAMERA:
		instance = std::make_shared<SubCameraRender>();
		m_renderTergets.push_back(instance);
		break;
	case RenderTergetType::SHADOW_MAP:
		instance = std::make_shared<ShadowMapRender>();
		m_renderTergets.push_back(instance);
		break;
	default:
		break;
	}
	 
	return instance;
}

void RenderTergetManager::ElaseRenderTerget(std::weak_ptr<RenderTerget> _renderTerget) {
	for (auto itr = m_renderTergets.begin(); itr != m_renderTergets.end(); itr++) {
		if ((*itr)->m_inceNum == _renderTerget.lock()->m_inceNum) {
			m_renderTergets.erase(itr);
		}
	}
}

void RenderTerget::SetRenderTerget() {
}

void RenderTerget::SetShaderResorce(int _number) {
	m_deviceContext->PSSetShaderResources(_number + 1, 1, m_shaderResourceView.GetAddressOf());
	m_deviceContext->PSGetSamplers(_number + 1, 1, m_samplerState.GetAddressOf());
	if(!m_worldMatrix.expired()&& !m_projectionMatrix.expired()&& !m_inversMatrix.expired())
	directx::SubResourceSendManager::GetInstance().SetCameraObjectBuffer(
		*m_worldMatrix.lock(),
		*m_projectionMatrix.lock(),
		*m_inversMatrix.lock(),
		*m_position
		);
	
}

void RenderTerget::SetCameraData(
	std::weak_ptr<math::Matrix> _worldMatrix, 
	std::weak_ptr<math::Matrix> _projectionMatrix, 
	std::weak_ptr<math::Matrix> _inversMatrix,
	math::Vector3* _position) {
	m_worldMatrix = _worldMatrix; 
	m_projectionMatrix= _projectionMatrix; 
	m_inversMatrix= _inversMatrix;
	m_position = _position;
}

ShadowMapRender::ShadowMapRender() {
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
	m_device->CreateTexture2D(
		&texDesc,
		NULL,
		m_texture2d.GetAddressOf());

	// レンダーターゲットビューの設定
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// レンダーターゲットビューの生成
	m_device->CreateRenderTargetView(
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
	m_device->CreateShaderResourceView(
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
	m_device->CreateSamplerState(
		&smpDesc,
		m_samplerState.GetAddressOf());
}

}
}