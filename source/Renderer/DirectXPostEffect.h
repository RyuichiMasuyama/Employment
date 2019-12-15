#pragma once

#ifdef DIRECTX11

#include "./DirectX/DirectX11Manager.h"
#include "./Shader/Shader.h"
#include "../Renderer/RenderObject.h"
#include "../AssetManager/MeshLoader.h"
#include <array>

namespace mslib {
namespace directx {
class DirectXPostEffect;
struct DirectXPostEffectStatus;
enum class DIRECTX_POSTEFFECT_TYPE :unsigned int;
}
namespace render {
using POSTEFFECT_TYPE = directx::DIRECTX_POSTEFFECT_TYPE;
using PostEffectStatus = directx::DirectXPostEffectStatus;
using CameraTexture = directx::ShaderTexture;
}

namespace directx {
enum class DIRECTX_POSTEFFECT_TYPE :unsigned int {
	GAUSS,
	BLOOM,
	MAX,
};
struct DirectXPostEffectStatus {
	bool OnFlag[static_cast<unsigned int>(DIRECTX_POSTEFFECT_TYPE::MAX)] = { false,false };

	std::array<float, 8> GaussPower;

	std::array<float, 8> BloomDiffusePower;
	float BloomSpecularPower;
};
class DirectXPostEffect {
public:
	DirectXPostEffect(render::CameraTexture _cameraTexture);
	~DirectXPostEffect() = default;

	// èáî‘
	// 1ÅDGauss
	// 2. Bloom
	void Rendering();

protected:
	DirectXPostEffectStatus m_postEffectStatus;

private:
	directx::PixelShader m_basic2dPS;
	directx::VertexShader m_basic2dVS;
	directx::InputLayout m_basic2dIL;

	std::array<shader::ShaderResource, static_cast<unsigned int>(DIRECTX_POSTEFFECT_TYPE::MAX)> m_shader;
	std::shared_ptr<render::MyMesh> m_mesh; 
	ShaderTexture m_resourceView;

	mslib::directx::RenderTargetView m_gaussRenderTergetView;
	mslib::directx::SamplerState m_gaussSamplerState;
	mslib::directx::ShaderTexture m_gaussShaderResourceView;
	mslib::directx::Texture2D m_gaussTexture2d;

	std::array<mslib::directx::RenderTargetView, 8> m_bloomRenderTergetView;
	std::array<mslib::directx::ShaderTexture, 8> m_bloomShaderResourceView;
	std::array<mslib::directx::Texture2D, 8> m_bloomTexture2d;
};

}
}

#endif // DIRECTX11