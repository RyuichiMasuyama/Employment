#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifdef DIRECTX11
#include "./DirectX/DirectX11Manager.h"
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
	Shader vertexShader = nullptr;
	Shader inputLayer = nullptr;
	Shader pixelShader = nullptr;
	Shader geometryShader = nullptr;
	Shader domainShader = nullptr;
	Shader hullShader = nullptr;
};
#endif



class ShaderLoader {
public:
	Shader Load(std::string _shaderName, ShaderType _shaderType);
//	template<class T>
//	void Load(std::string _shaderName, T comptr, ShaderType _shaderType) {
//		T asset = assets::AssetsManager::GetInstance().m_assets[_shaderName];
//
//#ifdef  DIRECTX11
//		// nullチェック
//		if (asset.operator Microsoft::WRL::Details::BoolType()) {
//			Shader weakShader;
//			asset.AsWeak(&weakShader);
//			return  weakShader;
//		}
//		directx::ShaderCompiler shaderCompiler;
//
//		switch (_shaderType)
//		{
//		case ShaderType::VS:
//			asset = shaderCompiler.Load(_shaderName, directx::ShaderType::VS);
//			break;
//		case ShaderType::PS:
//			asset = shaderCompiler.Load(_shaderName, directx::ShaderType::PS);
//			break;
//		case ShaderType::GS:
//			asset = shaderCompiler.Load(_shaderName, directx::ShaderType::GS);
//			break;
//		case ShaderType::HS:
//			asset = shaderCompiler.Load(_shaderName, directx::ShaderType::HS);
//			break;
//		case ShaderType::DS:
//			asset = shaderCompiler.Load(_shaderName, directx::ShaderType::DS);
//			break;
//		default:
//			break;
//		}
//		Shader weakShader;
//
//		assets::AssetsManager::GetInstance().m_assets[_shaderName] = asset;
//		// asset.AsWeak(&weakShader);
//
//		// return weakShader;
//#endif
//	}
};

}
}