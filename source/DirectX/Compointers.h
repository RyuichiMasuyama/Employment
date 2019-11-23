#pragma once

//DirectX11のAPI
#include <d3d11.h>

//DirectX11版のスマートポインタ
#include <wrl/client.h>

namespace mslib {
namespace directx {
typedef Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBuffer, VertexBuffer, IndexBuffer, StructuredBuffer;
typedef Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout;
typedef Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;
typedef Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
typedef Microsoft::WRL::ComPtr<ID3D11GeometryShader> GeometryShader;
typedef Microsoft::WRL::ComPtr<ID3D11ComputeShader> ComputeShader;
typedef Microsoft::WRL::ComPtr<ID3D11HullShader> HullShader;
typedef Microsoft::WRL::ComPtr<ID3D11DomainShader> DomainShader;
typedef Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture2D;
typedef Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ShaderTexture;
typedef Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> ComputeOutputView;
typedef Microsoft::WRL::ComPtr<ID3D11Device> Device;
typedef Microsoft::WRL::ComPtr<ID3D11DeviceContext> DeviceContext;
typedef Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;
typedef Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetView;
typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DepthStencilState;
typedef Microsoft::WRL::ComPtr<ID3D11RasterizerState>	RasterizerState;
typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DepthStencilView;
typedef Microsoft::WRL::ComPtr<ID3D11BlendState> AlphaEnableBlendingState, AlphaDisableBlendingState;
using SamplerState = Microsoft::WRL::ComPtr<ID3D11SamplerState>;
}
}