#pragma once

//DirectX11のAPI
#include <d3d11.h>

//シェーダコンパイラ
#include <d3dcompiler.h>

//DirectX11版のスマートポインタ
#include <wrl/client.h>

#include "./Compointers.h"
#include <Singleton.h>

//DirectXAPI関係のリンク
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace mslib {
namespace directx {
class DirectX11Manager :public  pattern::Singleton<DirectX11Manager>{
private:
	D3D_DRIVER_TYPE		m_driver_type;
	D3D_FEATURE_LEVEL	m_feature_level;

	mslib::directx::SwapChain			m_swap_chine;
	mslib::directx::Device				m_device;
	mslib::directx::DeviceContext		m_device_context;

	mslib::directx::RenderTargetView	m_render_target_view;
	mslib::directx::Texture2D			m_depth_stencil_buffer;
	mslib::directx::DepthStencilState	m_depth_stencil_state;
	mslib::directx::DepthStencilView	m_depth_stencil_view;
	mslib::directx::RasterizerState		m_rasterizer_state;
	mslib::directx::AlphaEnableBlendingState m_alpha_enable_blending_state;
	mslib::directx::AlphaDisableBlendingState m_alpha_disable_blending_state;

	mslib::directx::SamplerState		m_samplerState;
public:
	DirectX11Manager() = default;
	~DirectX11Manager() = default;

	void Init(HWND hWnd, bool fullscreen);

	//Getter
	mslib::directx::Device GetDevice();
	mslib::directx::DeviceContext GetDeviceContext();
	mslib::directx::SwapChain	GetSwapChain();

	mslib::directx::RenderTargetView GetRenderTargetView();
	mslib::directx::DepthStencilState GetDepthStencilState();
	mslib::directx::DepthStencilView GetDepthStencilView();

	void TurnOnAlphaBlending();
	void TurnOffAlphaBlending();
};

}
}