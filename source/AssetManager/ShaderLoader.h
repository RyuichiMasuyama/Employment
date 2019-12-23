#pragma once

#include "../Shader/Shader.h"

namespace mslib{
namespace loader {

class ShaderLoader {
public:
	shader::Shader Load(std::string _shaderName, shader::ShaderType _shaderType);

	template<class T>
	void Load(std::string _shaderName, T& _shader, shader::ShaderType _shaderType) {
		if (_shaderName == "null" || _shaderName == " ") {
			_shader = nullptr;
			return;
		}
#ifdef  DIRECTX11
		std::string stackName = _shaderName;
		if (_shaderType == shader::ShaderType::IL) {
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
		case shader::ShaderType::VS:
			asset = shaderCompiler.VSLoad(_shaderName);
			break;
		case shader::ShaderType::PS:
			asset = shaderCompiler.PSLoad(_shaderName);
			break;
		case shader::ShaderType::IL:
			asset = shaderCompiler.ILLoad(_shaderName);
			break;
		case shader::ShaderType::GS:
			asset = shaderCompiler.GSLoad(_shaderName);
			break;
		case shader::ShaderType::HS:
			asset = shaderCompiler.HSLoad(_shaderName);
			break;
		case shader::ShaderType::DS:
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