#pragma once

#include <array>
#include <map>
#include "./Mesh.h"
#include "./RenderObject.h"
#include "./Shader/Shader.h"
#include "./Assimp/AssimpSecen.h"
#include "./renderer/Material.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include "./AssetManager/ModelLoader.h"
#include "./Texture.h"

//#define TEXTURE_MAX 5
//#define INTER_POLATE_NUM 1
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

	// マテリアルセット
	void SetMaterial(std::string _fileName, int _number);
	void SetMaterial(MaterialData _mat, int _number);

	// テクスチャのセット
	void SetTexture(std::string _fileName, int _number);

	// 各種シェーダのセット
	void SetVertexShader(std::string _shaderName);
	void SetPixelShader(std::string _shaderName);
	void SetGeometryShader(std::string _shaderName);
	void SetHullShader(std::string _shaderName);
	void SetDomainShader(std::string _shaderName);
	void SetShader(std::string _shaderrName, shader::ShaderType _shaderType);

	// マテリアル取得
	std::vector<std::shared_ptr<MyMaterial>>* GetMaterialVectorPtr();
private:
	// メッシュ情報
	std::vector<std::shared_ptr<Mesh>> m_meshs;
	// マテリアル
	std::vector<std::shared_ptr<MyMaterial>> m_material;
	// シェーダー(内部でスマートポインタにしている)
	shader::Shaders m_shaders;
	// テクスチャ
	std::vector< texture::MyTexture > m_texture;
	// ボーンデータ
	std::map<std::string, render::Bone> m_bone;

	// アシンプ導入
	// ここにあるのはよくない
	// 実体がここにあるのでCopyコンストラクタを呼ぶとバグる
	// AssetManagerにアシンプを追加してポインタを保持できるようにする
	std::shared_ptr<assimp::AssimpScene> m_assimpScene;

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
	// マテリアルの解析と生成
	std::shared_ptr<Material> CreateMaterial(aiNode* node);

};
}
}