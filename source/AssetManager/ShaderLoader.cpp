#include "ShaderLoader.h"

namespace mslib {
namespace loader {

shader::Shader ShaderLoader::Load(std::string _shaderName, shader::ShaderType _shaderType) {

#ifdef  DIRECTX11
	auto a = std::any_cast<directx::PixelShader>(assets::AssetsManager::GetInstance().m_assets[_shaderName]);
	if (a) {
		return a;
	}
	shader::Shader weakShader;
	auto &asset = assets::AssetsManager::GetInstance().m_assets[_shaderName];
	directx::ShaderCompiler shaderCompiler;

	switch (_shaderType)
	{
	case shader::ShaderType::VS:
		asset = shaderCompiler.Load(_shaderName, directx::ShaderType::VS);
		break;
	case shader::ShaderType::PS: {
		auto aaa = shaderCompiler.Load(_shaderName, directx::ShaderType::PS);

		weakShader = (ID3D11PixelShader*)aaa.Get();// = (ID3D11PixelShader*)shaderCompiler.Load(_shaderName, directx::ShaderType::PS).Get();
												   // shaderCompiler.Load(_shaderName, directx::ShaderType::PS);
		break; }
	case shader::ShaderType::GS:
		asset = shaderCompiler.Load(_shaderName, directx::ShaderType::GS);
		break;
	case shader::ShaderType::HS:
		asset = shaderCompiler.Load(_shaderName, directx::ShaderType::HS);
		break;
	case shader::ShaderType::DS:
		asset = shaderCompiler.Load(_shaderName, directx::ShaderType::DS);
		break;
	default:
		break;
	}
	//Shader weakShader;

	// assets::AssetsManager::GetInstance().m_assets[_shaderName] = asset;
	//asset.AsWeak(&weakShader);

	return weakShader;
#endif
}
}
}