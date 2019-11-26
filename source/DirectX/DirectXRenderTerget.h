#pragma once

#ifdef DIRECTX11

#include "./DirectX/DirectX11Manager.h"
#include "./Renderer/RenderTerget.h"

namespace mslib {
namespace directx {

class DirectXRenderTerget :public render::RenderTerget {
public:
	DirectXRenderTerget(render::RenderTergetType _renderTergetType);
	~DirectXRenderTerget();

	void SetRenderTerget();
	void SetShaderResouce(int _number);

	void RenderBefor();

	// void Pipeline();
protected:
	mslib::directx::RenderTargetView m_renderTergetView;
	mslib::directx::SamplerState m_samplerState;
	mslib::directx::ShaderTexture m_shaderResourceView;
	mslib::directx::Texture2D m_texture2d;
};

class MainDirectXRenderTerget :public DirectXRenderTerget {
public:
	MainDirectXRenderTerget(render::RenderTergetType _renderTergetType);
};

class SubDirectXRenderTerget :public DirectXRenderTerget {
public:
	SubDirectXRenderTerget(render::RenderTergetType _renderTergetType);

};

class ShadowMapDirectXRenderTerget :public DirectXRenderTerget {
public:
	ShadowMapDirectXRenderTerget(render::RenderTergetType _renderTergetType);

};

}
}

#endif
