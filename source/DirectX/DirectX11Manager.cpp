#include "./DirectX/DirectX11Manager.h"

#include "./Windows/WindowsDefineData.h"

namespace mslib {
namespace directx {

void DirectX11Manager::Init(HWND hWnd, bool fullscreen) {
	//				(　2019/09/05　)
	//-----------よくわかってないゾーン-------------
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	HRESULT	hr = S_OK;
	IDXGIFactory* factory;				// factory
	IDXGIAdapter* adapter;				// videocard
	IDXGIOutput* adapterOutput;			// monitor
	unsigned int numModes;
	unsigned int numerator = 60;			// 分子
	unsigned int denominator = 1;			// 分母
	DXGI_MODE_DESC* displayModeList;
	D3D11_BLEND_DESC blendStateDescription;

	// ドライバの種類
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,					// Windows Advanced Rasterizer
		D3D_DRIVER_TYPE_REFERENCE,
	};
	unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

	unsigned int createDeviceFlags = 0;
	//   createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	// 機能レベル
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,					// DirectX11.1対応GPUレベル
		D3D_FEATURE_LEVEL_11_0,					// DirectX11対応GPUレベル
		D3D_FEATURE_LEVEL_10_1,					// DirectX10.1対応GPUレベル
		D3D_FEATURE_LEVEL_10_0,					// DirectX10対応GPUレベル
		D3D_FEATURE_LEVEL_9_3,					// DirectX9.3対応GPUレベル
		D3D_FEATURE_LEVEL_9_2,					// DirectX9.2対応GPUレベル
		D3D_FEATURE_LEVEL_9_1					// Direct9.1対応GPUレベル
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// Create a DirectX graphics interface factory
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(hr)) {
		//return false;
	}

	// use the factory to create an adpter for the primary graphics interface(video card)
	hr = factory->EnumAdapters(0, &adapter);
	if (FAILED(hr)) {
		//return false;
	}

	// enumerrate primary adapter output(monitor)
	hr = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(hr)) {
		//return false;
	}

	// get the number of modes that fit the DXGI_FORMAT_R8G8B8_UNORM display format forthe adapter output(monitor)
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr)) {
		//return false;
	}

	// create alist to hold all possible display modes for this monitor/video card combination
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList) {
		//return false;
	}

	// now fill the display mode list structures
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(hr)) {
		//return false;
	}

	// now go through all the display modes and find the one that matches the screen width and height
	// when a match is found store the numerator and denominator of the refresh rate for that monitor
	for (unsigned int i = 0; i < numModes; i++) {
		if (displayModeList[i].Width == SCREEN_X) {
			if (displayModeList[i].Height == SCREEN_Y) {
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	delete[] displayModeList;
	displayModeList = 0;

	adapterOutput->Release();
	adapterOutput = 0;

	adapter->Release();
	adapter = 0;

	factory->Release();
	factory = 0;

	//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
	//-----------よくわかってないゾーン-------------

	//　スワップチェインの設定
	//　画面のバッファ管理(ダブルバッファなど)
	//　サンプリングやリフレッシュレートが設定
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));

	scd.BufferCount = 1;	//ゼロクリア
	scd.BufferDesc.Width = SCREEN_X;		//スクリーンのサイズ横(バックバッファ)
	scd.BufferDesc.Height = SCREEN_Y;		//スクリーンのサイズ縦(バックバッファ)
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		//バックバッファフォーマット(RGB範囲0.0から1.0)
	scd.BufferDesc.RefreshRate.Numerator = numerator;
	scd.BufferDesc.RefreshRate.Denominator = denominator;	//リフレッシュレート(分母)
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		//バックバッファの使用方法
	scd.OutputWindow = hWnd;	//関連付けるウィンドウ
	scd.SampleDesc.Count = 1;		//マルチサンプルの数
	scd.SampleDesc.Quality = 0;		//マルチサンプルのクオリティ
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (fullscreen) {
		scd.Windowed = false;				// ウインドウモード
	}
	else {
		scd.Windowed = TRUE;				// ウインドウモード
	}
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	//モードの自動切換え

	for (UINT driver_typr_index = 0; driver_typr_index < numDriverTypes; driver_typr_index++) {

		m_driver_type = driverTypes[driver_typr_index];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,				// ディスプレイデバイスのアダプタ(NULLは自動散策)
			m_driver_type,		// デバイスドライバのタイプ
			NULL,				//	ソフトウェアラスタライザを使用する場合設定
			createDeviceFlags,	//　デバイスフラグ
			featureLevels,		//　機能レベル
			numFeatureLevels,	//　機能レベル数
			D3D11_SDK_VERSION,	//
			&scd,				//　スワップチェインの設定
			&m_swap_chine,		//　IDXGIDwapChainインタフェース
			&m_device,			//　デバイスのインタフェース
			&m_feature_level,	//　サポートされている機能レベル
			&m_device_context	//　デバイスコンテキスト
		);

		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) {
		//	return false;
	}

	//	レンダリングターゲットを作成
	//　バックバッファのポインタを取得
	ID3D11Texture2D* back_buffer = nullptr;
	hr = m_swap_chine->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
	if (FAILED(hr)) {
		//return false;
	}

	//バックバッファのポインタを指定してレンダーターゲットビューを作成
	hr = m_device->CreateRenderTargetView(back_buffer, NULL, &m_render_target_view);
	back_buffer->Release();
	back_buffer = nullptr;
	if (FAILED(hr)) {
		//return false;
	}

	//　Zバッファ
	D3D11_TEXTURE2D_DESC depth_buffer_desc;
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	D3D11_RASTERIZER_DESC raster_desc;

	ZeroMemory(&depth_buffer_desc, sizeof(depth_buffer_desc));

	depth_buffer_desc.Width = SCREEN_X;
	depth_buffer_desc.Height = SCREEN_Y;
	depth_buffer_desc.MipLevels = 1;
	depth_buffer_desc.ArraySize = 1;
	depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_buffer_desc.SampleDesc.Count = 1;
	depth_buffer_desc.SampleDesc.Quality = 0;
	depth_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	depth_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depth_buffer_desc.CPUAccessFlags = 0;
	depth_buffer_desc.MiscFlags = 0;

	hr = m_device->CreateTexture2D(&depth_buffer_desc, NULL, &m_depth_stencil_buffer);
	if (FAILED(hr)) {
		//return false;
	}
	//　ステンシルステート作成
	//　ステンシル設定構造体初期化
	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
	depth_stencil_desc.DepthEnable = true;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;

	// ディスクリプションの設定
	depth_stencil_desc.StencilEnable = true;
	depth_stencil_desc.StencilReadMask = 0xFF;
	depth_stencil_desc.StencilWriteMask = 0xFF;

	//　ステンシルオペレーションの設定(表面ポリゴン)
	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//　ステンシルオペレーションの設定(裏面ポリゴン)
	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//　深度ステンシルの生成
	hr = m_device->CreateDepthStencilState(&depth_stencil_desc, &m_depth_stencil_state);
	if (FAILED(hr)) {
		//return false;
	}

	//　デバイスコンテキストへセット
	m_device_context->OMSetDepthStencilState(m_depth_stencil_state.Get(), 1);

	//　ディプスステンシルビューの初期化
	ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));

	//　ディプスステンシルビューの設定
	depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;

	//ステンシルビューの生成
	hr = m_device->CreateDepthStencilView(m_depth_stencil_buffer.Get(), &depth_stencil_view_desc, &m_depth_stencil_view);
	//if (FALSE(hr)) {
	//	//return false;
	//}

	//レンダーターゲットビューと深度ステンシルバッファーを出力レンダーパイプラインにバインドする(グーグル先生)
	m_device_context->OMSetRenderTargets(1, m_render_target_view.GetAddressOf(), m_depth_stencil_view.Get());

	//描画する方法とポリゴンを決定するラスターの説明を設定します(グーグル先生)
	raster_desc.AntialiasedLineEnable = false;
	raster_desc.CullMode = D3D11_CULL_BACK;
	//raster_desc.CullMode = D3D11_CULL_NONE;//裏表描画
	raster_desc.DepthBias = 0;
	raster_desc.DepthBiasClamp = 0.f;
	raster_desc.DepthClipEnable = true;
	raster_desc.FillMode = D3D11_FILL_SOLID;
	raster_desc.FrontCounterClockwise = false;
	raster_desc.MultisampleEnable = false;
	raster_desc.ScissorEnable = false;
	raster_desc.SlopeScaledDepthBias = 0.f;

	//ラスタライザーの生成
	hr = m_device->CreateRasterizerState(&raster_desc, &m_rasterizer_state);
	//if (FALSE(hr)) {
	//	//return false;
	//}

	//ラスタライザーをセット
	m_device_context->RSSetState(m_rasterizer_state.Get());

	//ビューポートを設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_X;
	vp.Height = (FLOAT)SCREEN_Y;
	vp.MinDepth = 0.f;
	vp.MaxDepth = 1.f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	//ビューポートをセット
	m_device_context->RSSetViewports(1, &vp);

	//ブレンドステート初期化
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

	blendStateDescription.AlphaToCoverageEnable = FALSE;
	blendStateDescription.IndependentBlendEnable = FALSE;

	//ブレンドステート設定（アルファブレンド可）
	//blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	////blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	//blendStateDescription.RenderTarget[0] .SrcBlend = D3D11_BLEND_SRC_ALPHA;
	////blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR;
	//blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	////blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	////blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	//blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	//blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//blendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	/*blendStateDescription.AlphaToCoverageEnable = FALSE;
	blendStateDescription.IndependentBlendEnable = FALSE;
	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;*/

	//ブレンドステート作成
	hr = m_device->CreateBlendState(&blendStateDescription, m_alpha_disable_blending_state.GetAddressOf());
	if (FAILED(hr))
	{
		//return false;
	}

	//ブレンドステート設定（アルファブレンド不可）
	blendStateDescription.RenderTarget[0].BlendEnable = false;

	//ブレンドステート作成
	hr = m_device->CreateBlendState(&blendStateDescription, m_alpha_enable_blending_state.GetAddressOf());
	if (FAILED(hr))
	{
		//return false;
	}

	// サンプラーステートの設定
	D3D11_SAMPLER_DESC smpDesc;
	ZeroMemory(&smpDesc, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	smpDesc.MinLOD = 0;
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// サンプラーステート生成
	hr = m_device->CreateSamplerState(&smpDesc, m_samplerState.GetAddressOf());
	if (FAILED(hr)) {
		// return false;
	}

	// サンプラーステートを転送
	m_device_context->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());

}

mslib::directx::Device DirectX11Manager::GetDevice()
{
	return m_device;
}

mslib::directx::DeviceContext DirectX11Manager::GetDeviceContext()
{
	return m_device_context;
}
mslib::directx::SwapChain DirectX11Manager::GetSwapChain()
{
	return m_swap_chine;
}
mslib::directx::RenderTargetView DirectX11Manager::GetRenderTargetView()
{
	return m_render_target_view;
}
mslib::directx::DepthStencilState DirectX11Manager::GetDepthStencilState()
{
	return m_depth_stencil_state;
}
mslib::directx::DepthStencilView DirectX11Manager::GetDepthStencilView()
{
	return m_depth_stencil_view;
}

mslib::directx::SamplerState DirectX11Manager::GetSamplerState()
{
	return m_samplerState;
}

void DirectX11Manager::TurnOnAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	//アルファブレンドをONにする
	m_device_context->OMSetBlendState(m_alpha_disable_blending_state.Get(), blendFactor, 0xffffffff);
	return;
}

void DirectX11Manager::TurnOffAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	//アルファブレンドをOFFにする
	m_device_context->OMSetBlendState(m_alpha_enable_blending_state.Get(), blendFactor, 0xffffffff);
	return;
}
}
}