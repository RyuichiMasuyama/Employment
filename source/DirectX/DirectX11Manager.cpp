#include "./DirectX/DirectX11Manager.h"

#include "./Windows/WindowsDefineData.h"

namespace mslib {
namespace directx {

void DirectX11Manager::Init(HWND hWnd, bool fullscreen) {
	//				(�@2019/09/05�@)
	//-----------�悭�킩���ĂȂ��]�[��-------------
	//����������������������������������������������

	HRESULT	hr = S_OK;
	IDXGIFactory* factory;				// factory
	IDXGIAdapter* adapter;				// videocard
	IDXGIOutput* adapterOutput;			// monitor
	unsigned int numModes;
	unsigned int numerator = 60;			// ���q
	unsigned int denominator = 1;			// ����
	DXGI_MODE_DESC* displayModeList;
	D3D11_BLEND_DESC blendStateDescription;

	// �h���C�o�̎��
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,					// Windows Advanced Rasterizer
		D3D_DRIVER_TYPE_REFERENCE,
	};
	unsigned int numDriverTypes = ARRAYSIZE(driverTypes);

	unsigned int createDeviceFlags = 0;
	//   createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	// �@�\���x��
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,					// DirectX11.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_11_0,					// DirectX11�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_1,					// DirectX10.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_0,					// DirectX10�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_3,					// DirectX9.3�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_2,					// DirectX9.2�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_1					// Direct9.1�Ή�GPU���x��
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

	//����������������������������������������������
	//-----------�悭�킩���ĂȂ��]�[��-------------

	//�@�X���b�v�`�F�C���̐ݒ�
	//�@��ʂ̃o�b�t�@�Ǘ�(�_�u���o�b�t�@�Ȃ�)
	//�@�T���v�����O�⃊�t���b�V�����[�g���ݒ�
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));

	scd.BufferCount = 1;	//�[���N���A
	scd.BufferDesc.Width = SCREEN_X;		//�X�N���[���̃T�C�Y��(�o�b�N�o�b�t�@)
	scd.BufferDesc.Height = SCREEN_Y;		//�X�N���[���̃T�C�Y�c(�o�b�N�o�b�t�@)
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		//�o�b�N�o�b�t�@�t�H�[�}�b�g(RGB�͈�0.0����1.0)
	scd.BufferDesc.RefreshRate.Numerator = numerator;
	scd.BufferDesc.RefreshRate.Denominator = denominator;	//���t���b�V�����[�g(����)
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		//�o�b�N�o�b�t�@�̎g�p���@
	scd.OutputWindow = hWnd;	//�֘A�t����E�B���h�E
	scd.SampleDesc.Count = 1;		//�}���`�T���v���̐�
	scd.SampleDesc.Quality = 0;		//�}���`�T���v���̃N�I���e�B
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (fullscreen) {
		scd.Windowed = false;				// �E�C���h�E���[�h
	}
	else {
		scd.Windowed = TRUE;				// �E�C���h�E���[�h
	}
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	//���[�h�̎����؊���

	for (UINT driver_typr_index = 0; driver_typr_index < numDriverTypes; driver_typr_index++) {

		m_driver_type = driverTypes[driver_typr_index];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,				// �f�B�X�v���C�f�o�C�X�̃A�_�v�^(NULL�͎����U��)
			m_driver_type,		// �f�o�C�X�h���C�o�̃^�C�v
			NULL,				//	�\�t�g�E�F�A���X�^���C�U���g�p����ꍇ�ݒ�
			createDeviceFlags,	//�@�f�o�C�X�t���O
			featureLevels,		//�@�@�\���x��
			numFeatureLevels,	//�@�@�\���x����
			D3D11_SDK_VERSION,	//
			&scd,				//�@�X���b�v�`�F�C���̐ݒ�
			&m_swap_chine,		//�@IDXGIDwapChain�C���^�t�F�[�X
			&m_device,			//�@�f�o�C�X�̃C���^�t�F�[�X
			&m_feature_level,	//�@�T�|�[�g����Ă���@�\���x��
			&m_device_context	//�@�f�o�C�X�R���e�L�X�g
		);

		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) {
		//	return false;
	}

	//	�����_�����O�^�[�Q�b�g���쐬
	//�@�o�b�N�o�b�t�@�̃|�C���^���擾
	ID3D11Texture2D* back_buffer = nullptr;
	hr = m_swap_chine->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
	if (FAILED(hr)) {
		//return false;
	}

	//�o�b�N�o�b�t�@�̃|�C���^���w�肵�ă����_�[�^�[�Q�b�g�r���[���쐬
	hr = m_device->CreateRenderTargetView(back_buffer, NULL, &m_render_target_view);
	back_buffer->Release();
	back_buffer = nullptr;
	if (FAILED(hr)) {
		//return false;
	}

	//�@Z�o�b�t�@
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
	//�@�X�e���V���X�e�[�g�쐬
	//�@�X�e���V���ݒ�\���̏�����
	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
	depth_stencil_desc.DepthEnable = true;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;

	// �f�B�X�N���v�V�����̐ݒ�
	depth_stencil_desc.StencilEnable = true;
	depth_stencil_desc.StencilReadMask = 0xFF;
	depth_stencil_desc.StencilWriteMask = 0xFF;

	//�@�X�e���V���I�y���[�V�����̐ݒ�(�\�ʃ|���S��)
	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//�@�X�e���V���I�y���[�V�����̐ݒ�(���ʃ|���S��)
	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//�@�[�x�X�e���V���̐���
	hr = m_device->CreateDepthStencilState(&depth_stencil_desc, &m_depth_stencil_state);
	if (FAILED(hr)) {
		//return false;
	}

	//�@�f�o�C�X�R���e�L�X�g�փZ�b�g
	m_device_context->OMSetDepthStencilState(m_depth_stencil_state.Get(), 1);

	//�@�f�B�v�X�X�e���V���r���[�̏�����
	ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));

	//�@�f�B�v�X�X�e���V���r���[�̐ݒ�
	depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;

	//�X�e���V���r���[�̐���
	hr = m_device->CreateDepthStencilView(m_depth_stencil_buffer.Get(), &depth_stencil_view_desc, &m_depth_stencil_view);
	//if (FALSE(hr)) {
	//	//return false;
	//}

	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���o�b�t�@�[���o�̓����_�[�p�C�v���C���Ƀo�C���h����(�O�[�O���搶)
	m_device_context->OMSetRenderTargets(1, m_render_target_view.GetAddressOf(), m_depth_stencil_view.Get());

	//�`�悷����@�ƃ|���S�������肷�郉�X�^�[�̐�����ݒ肵�܂�(�O�[�O���搶)
	raster_desc.AntialiasedLineEnable = false;
	raster_desc.CullMode = D3D11_CULL_BACK;
	//raster_desc.CullMode = D3D11_CULL_NONE;//���\�`��
	raster_desc.DepthBias = 0;
	raster_desc.DepthBiasClamp = 0.f;
	raster_desc.DepthClipEnable = true;
	raster_desc.FillMode = D3D11_FILL_SOLID;
	raster_desc.FrontCounterClockwise = false;
	raster_desc.MultisampleEnable = false;
	raster_desc.ScissorEnable = false;
	raster_desc.SlopeScaledDepthBias = 0.f;

	//���X�^���C�U�[�̐���
	hr = m_device->CreateRasterizerState(&raster_desc, &m_rasterizer_state);
	//if (FALSE(hr)) {
	//	//return false;
	//}

	//���X�^���C�U�[���Z�b�g
	m_device_context->RSSetState(m_rasterizer_state.Get());

	//�r���[�|�[�g��ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_X;
	vp.Height = (FLOAT)SCREEN_Y;
	vp.MinDepth = 0.f;
	vp.MaxDepth = 1.f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	//�r���[�|�[�g���Z�b�g
	m_device_context->RSSetViewports(1, &vp);

	//�u�����h�X�e�[�g������
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

	blendStateDescription.AlphaToCoverageEnable = FALSE;
	blendStateDescription.IndependentBlendEnable = FALSE;

	//�u�����h�X�e�[�g�ݒ�i�A���t�@�u�����h�j
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

	//�u�����h�X�e�[�g�쐬
	hr = m_device->CreateBlendState(&blendStateDescription, m_alpha_disable_blending_state.GetAddressOf());
	if (FAILED(hr))
	{
		//return false;
	}

	//�u�����h�X�e�[�g�ݒ�i�A���t�@�u�����h�s�j
	blendStateDescription.RenderTarget[0].BlendEnable = false;

	//�u�����h�X�e�[�g�쐬
	hr = m_device->CreateBlendState(&blendStateDescription, m_alpha_enable_blending_state.GetAddressOf());
	if (FAILED(hr))
	{
		//return false;
	}

	// �T���v���[�X�e�[�g�̐ݒ�
	D3D11_SAMPLER_DESC smpDesc;
	ZeroMemory(&smpDesc, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	smpDesc.MinLOD = 0;
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// �T���v���[�X�e�[�g����
	hr = m_device->CreateSamplerState(&smpDesc, m_samplerState.GetAddressOf());
	if (FAILED(hr)) {
		// return false;
	}

	// �T���v���[�X�e�[�g��]��
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

	//�A���t�@�u�����h��ON�ɂ���
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

	//�A���t�@�u�����h��OFF�ɂ���
	m_device_context->OMSetBlendState(m_alpha_enable_blending_state.Get(), blendFactor, 0xffffffff);
	return;
}
}
}