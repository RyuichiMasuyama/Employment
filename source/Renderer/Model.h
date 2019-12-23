#pragma once

#include "./Mesh.h"
#include "./RenderObject.h"
#include "../AssetManager/TextureLoader.h"
#include "../Shader/Shader.h"

namespace mslib {
namespace render {
class ModelData {
public:
	// コンストラクタ・デストラクタ
	ModelData() = default;
	~ModelData() = default;

	void Load();

	// 描画
	void Draw();

	// シェーダのセット
	void SetTexture(texture::Texture _texture);

	// 各種シェーダのセット
	void SetVertexShader(shader::VertexShader _shader);
	void SetPixelShader(shader::PixelShader _shader);
	void SetGeometryShader(shader::GeometryShader _shader);
	void SetHullShader(shader::HullShader _shader);
	void SetDomainShader(shader::DomainShader _shader);
private:
	// メッシュ情報
	std::vector<std::shared_ptr<Mesh>> m_meshs;
	// マテリアル
	std::shared_ptr<Material> m_material;
	// シェーダー(内部でスマートポインタにしている)
	shader::ShaderResource m_shaders;
};
}
}