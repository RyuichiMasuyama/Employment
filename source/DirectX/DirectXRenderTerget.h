#pragma once

#ifdef DIRECTX11

#include "./DirectX/DirectX11Manager.h"
#include "./Renderer/RenderTerget.h"

namespace mslib {
namespace render {
using CameraTexture = mslib::directx::ShaderTexture;
}
}

namespace mslib {
namespace directx {

class DirectXRenderTerget :public render::RenderTerget {
public:
	DirectXRenderTerget(render::RenderTergetType _renderTergetType);
	~DirectXRenderTerget();

	void SetRenderTerget();
	void SetShaderResouce(int _number);

	void BufferClear();

	virtual void UniqueProcess() {};

	render::CameraTexture GetCameraTexture();

	// void Pipeline();
protected:
	std::weak_ptr<math::Matrix> GetCameraPorjection();

	mslib::directx::RenderTargetView m_renderTergetView;
	mslib::directx::SamplerState m_samplerState;
	mslib::directx::ShaderTexture m_shaderResourceView;
	mslib::directx::Texture2D m_texture2d;
	float m_color[4];
};

class MainDirectXRenderTerget :public DirectXRenderTerget {
public:
	MainDirectXRenderTerget();
};

class SubDirectXRenderTerget :public DirectXRenderTerget {
public:
	SubDirectXRenderTerget();
};

class ShadowMapDirectXRenderTerget :public DirectXRenderTerget {
public:
	ShadowMapDirectXRenderTerget();
private:
	static const math::Matrix SHADOW_BIAS;
	void UniqueProcess() override;
	
	PixelShader m_ps;
	VertexShader m_vs;
	InputLayout m_il;
};

class BasicDirectXRenderTerget :public DirectXRenderTerget {
public:
	BasicDirectXRenderTerget();
};

class PostEffectDirectXRenderTerget :public DirectXRenderTerget {
	PostEffectDirectXRenderTerget();
};

}
}

#endif
