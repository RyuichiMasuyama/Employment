#pragma once

#include <string>
#include <vector>

#ifdef DIRECTX11

#include "../DirectX/DirectX11Manager.h"

#endif // DIRECTX11


namespace mslib {
namespace assets {

#ifdef DIRECTX11
using AssetBase = directx::D3D11BaseComptr;
#endif

}
namespace directx {
//シェーダーをコンパイルする関数
//鈴木先生のソースコード参考
//ジオメトリシェーダーなどに併用も可能確認(ZeroGram様ブログ参照)
HRESULT CompileShaderFromFile(const char * _file_name, LPCSTR _main_fanction_name, LPCSTR _shader_version, ID3DBlob** _compile_shader);

enum INPUT_LAYOUT_NAME;

enum class ShaderType {
	VS,
	IL,
	PS,
	GS,
	DS,
	HS
};

enum INPUT_LAYOUT_NAME :unsigned int {
	INPUT_LAYOUT_POS_NORMAL,
	INPUT_LAYOUT_POS_COLOR,
	INPUT_LAYOUT_POS_NORMAL_COLOR,
	INPUT_LAYOUT_POS_NORMAL_TEXCOORD,
	INPUT_LAYOUT_POS_NORMAL_TEXCOORD_COLOR,
	INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD,
	INPUT_LAYOUT_POS_NORMAL_TANGENT_BINORMAL_TEXCOORD,
	INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD_COLOR,
	INPUT_LAYOUT_POS_NORMAL_TANGENT_BINORMAL_TEXCOORD_COLOR,
	INPUT_LAYOUT_MAX
};

#ifdef DIRECTX11

#endif // DIRECTX11

class ShaderCompiler {
public:
	assets::AssetBase Load(std::string _shaderName, ShaderType _shaderType);

	directx::PixelShader PSLoad(std::string _shaderName);
	directx::VertexShader VSLoad(std::string _shaderName);
	directx::InputLayout ILLoad(std::string _shaderName);
	directx::GeometryShader GSLoad(std::string _shaderName);
	directx::HullShader HSLoad(std::string _shaderName);
	directx::DomainShader DSLoad(std::string _shaderName);
private:
	void InputLayoutPick(INPUT_LAYOUT_NAME _input_layout_name, std::vector<D3D11_INPUT_ELEMENT_DESC>& element);

};

}
}