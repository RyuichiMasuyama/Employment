#pragma once

#include <array>
#include <map>
#include "./Mesh.h"
#include "./RenderObject.h"
#include "./Shader/Shader.h"
#include "./Assimp/AssimpSecen.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include "./AssetManager/ModelLoader.h"
#include "./AssetManager/TextureLoader.h"

namespace mslib {
namespace render {

class ModelData {
	static constexpr const int TEXTURE_MAX = 5;
	static constexpr const int INTER_POLATE_NUM = 1;
public:
	// コンストラクタ・デストラクタ
	ModelData() = default;
	~ModelData() = default;

	// モデルのロード
	void Load(std::string _fileName);
	// 描画
	void Draw();

	void AnimationUpdate(unsigned int _animeNo,unsigned int _animeFileNo);

	// シェーダのセット
	void SetTexture(texture::Texture _texture, int _number);

	// 各種シェーダのセット
	void SetVertexShader(std::string _shadeName);
	void SetPixelShader(std::string _shadeName);
	void SetGeometryShader(std::string _shadeName);
	void SetHullShader(std::string _shadeName);
	void SetDomainShader(std::string _shadeName);
private:
	// メッシュ情報
	std::vector<std::shared_ptr<Mesh>> m_meshs;
	// マテリアル
	std::shared_ptr<Material> m_material;
	// シェーダー(内部でスマートポインタにしている)
	shader::Shaders m_shaders;
	// テクスチャ
	std::array< texture::Texture, TEXTURE_MAX > m_texture;
	// ボーンデータ
	std::map<std::string, render::Bone> m_bone;
	// アシンプ導入
	// ここにあるのはよくない
	assimp::AssimpScene m_assimpScene;

	// キーフレームアニメーションデータ
	int m_Frame = 0;							// フレーム番号
	int m_cnt = 0;								// キーフレーム補間用
	int m_preFrame = 0;							// キーフレーム補間用
	float m_factor = 0.0f;						// キーフレーム補間用

	// アシンプ補助関数
	// ボーン情報の解析と保持
	void CreateBone(aiNode* node);
	// ノードの解析
	void ProcessNode(aiNode* _node, const aiScene* _scene);
	// メッシュを解析
	std::shared_ptr<Mesh> ProcessMesh(aiMesh* _mesh, const aiScene* _scene, unsigned int _meshidx);
	// 再帰的にボーン更新
	void UpdateBoneMatrix(aiNode* node, math::Matrix _mat);
	void LoadMaterialTextures(
		aiMaterial * _mat,
		aiTextureType _type,
		std::string _typeName,
		const aiScene * _scene);

};
}
}