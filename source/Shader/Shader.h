#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "./AssetManager/AssetManager.h"

#ifdef DIRECTX11
#include "./DirectX/DirectX11Manager.h"
#include "./ShaderCompiler.h"
#endif

#include <string>

////各種シェーダーのマネージャ
//#include "MyDirectXVertexShader.h"
//#include "MyDirectXPixelShader.h"
//#include "MyDirectXGeometryShader.h"

#define SHADER_NAME_MAX 256

//前方宣言
namespace mslib {
namespace shader {

#ifdef DIRECTX11
// using Shader = Microsoft::WRL::WeakRef;
using Shader = directx::PixelShader;

enum class ShaderType {
	VS,
	IL,
	PS,
	GS,
	DS,
	HS
};

using VertexShader = directx::VertexShader;
using InputLayer = directx::InputLayout;
using PixelShader = directx::PixelShader;
using GeometryShader = directx::GeometryShader;
using DomainShader = directx::DomainShader;
using HullShader = directx::HullShader;


//シェーダをまとめたクラス
struct ShaderResource {
	VertexShader vertexShader = nullptr;
	InputLayer inputLayer = nullptr;
	PixelShader pixelShader = nullptr;
	GeometryShader geometryShader = nullptr;
	DomainShader domainShader = nullptr;
	HullShader hullShader = nullptr;
};
#endif



class ShaderLoader {
public:
	Shader Load(std::string _shaderName, ShaderType _shaderType);

	template<class T>
	void Load(std::string _shaderName, T& _shader, ShaderType _shaderType) {
		if (_shaderName == "null" || _shaderName == " ") {
			_shader = nullptr;
			return ;
		}
#ifdef  DIRECTX11
		std::string stackName = _shaderName;
		if (_shaderType == ShaderType::IL) {
			stackName += "IL";
		}
		auto asset = assets::AssetsManager::GetInstance().m_assets[stackName];
		if (asset.has_value()) {
			_shader = std::any_cast<T>(asset);
			return;
		}
		directx::ShaderCompiler shaderCompiler;

		switch (_shaderType)
		{
		case ShaderType::VS:
			asset = shaderCompiler.VSLoad(_shaderName);
			break;
		case ShaderType::PS:
			asset = shaderCompiler.PSLoad(_shaderName);
			break;
		case ShaderType::IL:
			asset = shaderCompiler.ILLoad(_shaderName);
			break;
		case ShaderType::GS:
			asset = shaderCompiler.GSLoad(_shaderName);
			break;
		case ShaderType::HS:
			asset = shaderCompiler.HSLoad(_shaderName);
			break;
		case ShaderType::DS:
			asset = shaderCompiler.DSLoad(_shaderName);
			break;
		default:
			break;
		}
		_shader = std::any_cast<T>(asset);
#endif
	}

};

}
}