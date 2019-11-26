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


class BufferCreater {
public:
	// BufferCreater(mslib::directx::Device _device) :m_device(_device) {}
	BufferCreater() :m_device(DirectX11Manager::GetInstance().GetDevice()) {}

	ID3D11Buffer* CreateConstantBuffer(UINT _byte_size);
	ID3D11Buffer* CreateIndexBuffer(UINT* Index, UINT IndexNum);

	template<class T>
	ID3D11Buffer* CreateVertexBuffer(T*_vertex_data, UINT _vertex_num) {
		//頂点バッファ作成
		D3D11_BUFFER_DESC buffer_desc;
		ZeroMemory(&buffer_desc, sizeof(buffer_desc));
		buffer_desc.ByteWidth = sizeof(T) * _vertex_num;
		buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buffer_desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subresource_data;
		ZeroMemory(&subresource_data, sizeof(subresource_data));
		subresource_data.pSysMem = _vertex_data;

		ID3D11Buffer* buffer;
		if (FAILED(m_device->CreateBuffer(&buffer_desc, &subresource_data, &buffer))) {
			return nullptr;
		}
		return buffer;
	};

private:
	mslib::directx::Device m_device;
};
}
}