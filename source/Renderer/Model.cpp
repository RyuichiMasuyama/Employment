#include "./Model.h"
#include "./AssetManager/TextureLoader.h"
#include "./AssetManager/ShaderLoader.h"

namespace mslib {
namespace render {
void ModelData::Load(std::string _fileName) {
	bool sts = m_assimpScene.Init(_fileName);

	// m_directory = resourcefolder;		// このモデルのテクスチャが存在するディレクトリ

	// ボーンを生成する
	CreateBone(m_assimpScene.GetScene()->mRootNode);

	// ボーンの配列位置を格納する
	unsigned int num = 0;
	for (auto& itr : m_bone) {
		itr.second.idx = num;
		num++;
	}
	// aiノードを解析する
	ProcessNode(m_assimpScene.GetScene()->mRootNode, m_assimpScene.GetScene());
	//auto mesh = std::make_shared< render::Mesh >();

	//std::vector<PolygonAnimationVertex> vertices;			// 頂点
	//std::vector<PolygonIndex> indices;		// 面の構成情報
	//PolygonAnimationVertex ver;
	//PolygonIndex ind;
	//
	//ver.pos.x = -0.5f;
	//ver.pos.y = 0.5f;
	//ver.pos.z = 0.f;

	//ver.normal.x = 0.f;
	//ver.normal.y = 0.f;
	//ver.normal.z = -1.f;

	//vertices.push_back(ver);
	//indices.push_back(0);

	//ver.pos.x = 0.5f;
	//ver.pos.y = 0.5f;
	//ver.pos.z = 0.f;

	//ver.normal.x = 0.f; 
	//ver.normal.y = 0.f;
	//ver.normal.z = -1.f;

	//vertices.push_back(ver);
	//indices.push_back(1);

	//ver.pos.x = -0.5f;
	//ver.pos.y = -0.5f;
	//ver.pos.z = 0.f;

	//ver.normal.x = 0.f;
	//ver.normal.y = 0.f;
	//ver.normal.z = -1.f;

	//vertices.push_back(ver);
	//indices.push_back(2);

	//mesh->Load(vertices, indices);
	//m_meshs.push_back(mesh);

	return;
}
void ModelData::Draw() {
	m_shaders.Send();
	for (int i = 0; i < m_texture.size(); i++) {
		m_texture[i].Send(i);
	}

	for (auto& itr : m_meshs) {
		itr->Draw();
	}
}

void ModelData::AnimationUpdate(unsigned int _animeNo, unsigned int _animeFileNo)
{
	// 0番目のシーンを取り出し
	const aiScene* scene = m_assimpScene.GetScene();

	// アニメーションデータを持っているか？
	if (scene->HasAnimations())
	{
		//アニメーションデータからボーンマトリクス算出
		aiAnimation* animation = scene->mAnimations[_animeNo];

		// ボーンの数だけループ
		for (unsigned int c = 0; c < animation->mNumChannels; c++)
		{
			aiNodeAnim* nodeAnim = animation->mChannels[c];

			// ボーン存在チェック(アニメーションにのみ存在するボーンがあった場合は無視する)
			auto itr = m_bone.find(nodeAnim->mNodeName.C_Str());
			if (itr != m_bone.end()) {
				Bone* bone = &m_bone[nodeAnim->mNodeName.C_Str()];

				int f1, f2;

				f1 = m_Frame % nodeAnim->mNumRotationKeys;//簡易実装   
				aiQuaternion rot1 = nodeAnim->mRotationKeys[f1].mValue; // クオータニオン

				f1 = m_Frame % nodeAnim->mNumPositionKeys;//簡易実装
				aiVector3D pos1 = nodeAnim->mPositionKeys[f1].mValue;

				f2 = m_preFrame % nodeAnim->mNumRotationKeys;//簡易実装  
				aiQuaternion rot2 = nodeAnim->mRotationKeys[f2].mValue; // クオータニオン

				f2 = m_preFrame % nodeAnim->mNumPositionKeys;//簡易実装	
				aiVector3D pos2 = nodeAnim->mPositionKeys[f2].mValue;

				// 補間
				rot1.Interpolate(rot1, rot1, rot2, m_factor);
				pos1.x = pos1.x * (1.0f - m_factor) + pos2.x * (m_factor);
				pos1.y = pos1.y * (1.0f - m_factor) + pos2.y * (m_factor);
				pos1.z = pos1.z * (1.0f - m_factor) + pos2.z * (m_factor);

				bone->animationMatrix = math::Matrix(
					1.0f, 1.0f, 1.0f, 0.f,
					(float)rot1.x, (float)rot1.y, (float)rot1.z, (float)rot1.w,
					(float)pos1.x, (float)pos1.y, (float)pos1.z, 0.f,
					0.f, 0.f, 0.f, 0.f);
				// bone->animationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot1, pos1);
			}
		}

		//再帰的にボーンマトリクスを更新
		UpdateBoneMatrix(m_assimpScene.GetScene()->mRootNode, math::Matrix());

		// メッシュのOBB更新
		//		for (int i = 0; i < m_meshes.size(); i++)
		//		{
		//			m_meshes[i].UpdateOBB(m_Bone,mtxworld);
		//		}
	}

	if (m_cnt % INTER_POLATE_NUM == 0) {
		m_preFrame = m_Frame;
		m_Frame++;
		m_factor = 0;
	}

	m_factor = 1.0f / (float)(m_cnt % INTER_POLATE_NUM + 1);

	m_cnt++;
}

void ModelData::SetTexture(std::string _fileName, int _number) {
	if (_number<m_texture.size()) {
		m_texture[_number].Load(_fileName);
	}
}

void ModelData::SetVertexShader(std::string _shaderName) {
	loader::ShaderLoader loader;
	shader::VertexShader vs;
	shader::InputLayer il;
	loader.Load(_shaderName, il, shader::ShaderType::IL);
	loader.Load(_shaderName, vs, shader::ShaderType::VS);
	m_shaders.SetInputLayout(il);
	m_shaders.SetVertexShader(vs);
}

void ModelData::SetPixelShader(std::string _shaderName) {
	loader::ShaderLoader loader;
	shader::PixelShader ps;
	loader.Load(_shaderName, ps, shader::ShaderType::PS);
	m_shaders.SetPixelShader(ps);
}

void ModelData::SetGeometryShader(std::string _shaderName) {
	loader::ShaderLoader loader;
	shader::GeometryShader gs;
	loader.Load(_shaderName, gs, shader::ShaderType::GS);
	m_shaders.SetGeometryShader(gs);
}

void ModelData::SetHullShader(std::string _shaderName) {
	loader::ShaderLoader loader;
	shader::HullShader hl;
	loader.Load(_shaderName, hl, shader::ShaderType::HS);
	m_shaders.SetHullShader(hl);
}

void ModelData::SetDomainShader(std::string _shaderName) {
	loader::ShaderLoader loader;
	shader::DomainShader ds;
	loader.Load(_shaderName, ds, shader::ShaderType::DS);
	m_shaders.SetDomainShader(ds);
}

void ModelData::SetShader(std::string _shaderName, shader::ShaderType _shaderType) {
	loader::ShaderLoader loader;
	switch(_shaderType) {
	case shader::ShaderType::VS: {
		shader::VertexShader vs;
		shader::InputLayer il;
		loader.Load(_shaderName, il, shader::ShaderType::IL);
		loader.Load(_shaderName, vs, shader::ShaderType::VS);
		m_shaders.SetInputLayout(il);
		m_shaders.SetVertexShader(vs);

	}
		break;
	case shader::ShaderType::PS: {
		shader::PixelShader ps;
		loader.Load(_shaderName, ps, shader::ShaderType::PS);
		m_shaders.SetPixelShader(ps);

	}
		break;
	case shader::ShaderType::GS: {
		shader::GeometryShader gs;
		loader.Load(_shaderName, gs, shader::ShaderType::GS);
		m_shaders.SetGeometryShader(gs);

	}
		break;
	case shader::ShaderType::HS: {
		shader::HullShader hl;
		loader.Load(_shaderName, hl, shader::ShaderType::HS);
		m_shaders.SetHullShader(hl);

	}
		break;
	case shader::ShaderType::DS: {
		shader::DomainShader ds;
		loader.Load(_shaderName, ds, shader::ShaderType::DS);
		m_shaders.SetDomainShader(ds);

	}
		break;

	}
	return ;
}

void ModelData::CreateBone(aiNode *node) {
	Bone bone;

	// ノード名をキーにしてボーン情報を保存
	m_bone[node->mName.C_Str()] = bone;

	for (unsigned int n = 0; n < node->mNumChildren; n++)
	{
		CreateBone(node->mChildren[n]);
	}
}

void ModelData::ProcessNode(aiNode * _node, const aiScene * _scene) {
	// ノード内のメッシュの数分ループする
	for (unsigned int i = 0; i < _node->mNumMeshes; i++)
	{
		int meshIndex = _node->mMeshes[i];			// ノードのi番目メッシュのインデックスを取得
		aiMesh* mesh = _scene->mMeshes[meshIndex];	// シーンからメッシュ本体を取り出す

		m_meshs.push_back(this->ProcessMesh(mesh, _scene, meshIndex));
	}

	// 子ノードについても解析
	for (unsigned int i = 0; i < _node->mNumChildren; i++)
	{
		// 再帰分なので一応自クラスと示すためにthisポインタ参照
		this->ProcessNode(_node->mChildren[i], _scene);
	}
}

std::shared_ptr< Mesh > ModelData::ProcessMesh(aiMesh * _mesh, const aiScene * _scene, unsigned int _meshidx) {
	auto newMesh = std::make_shared<Mesh>();
	std::vector<PolygonAnimationVertex> vertices;			// 頂点
	std::vector<PolygonIndex> indices;		// 面の構成情報
	// std::vector<Texture> textures;			// テクスチャ
	
	// 頂点情報を取得
	for (unsigned int i = 0; i < _mesh->mNumVertices; i++)
	{
		PolygonAnimationVertex vertex;

		vertex.pos.x = _mesh->mVertices[i].x;
		vertex.pos.y = _mesh->mVertices[i].y;
		vertex.pos.z = _mesh->mVertices[i].z;

		// 法線ベクトルが存在するか？
		if (_mesh->HasNormals()) {
			vertex.normal.x = _mesh->mNormals[i].x;
			vertex.normal.y = _mesh->mNormals[i].y;
			vertex.normal.z = _mesh->mNormals[i].z;
		}
		else {
			vertex.normal.x = 0.0f;
			vertex.normal.y = 0.0f;
			vertex.normal.z = 0.0f;
		}

		// テクスチャ座標（０番目）が存在するか？
		if (_mesh->HasTextureCoords(0)) {
			vertex.tex.x = _mesh->mTextureCoords[0][i].x;
			vertex.tex.y = _mesh->mTextureCoords[0][i].y;
		}
/*
		vertex.boneNum = 0;

		for (unsigned int b = 0; b < 4; b++)
		{
			vertex.boneIndex[b] = -1;
			vertex.boneWeight[b] = 0.0f;
		}*/

		vertices.push_back(vertex);
	}

	// 面の構成情報を取得
	for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
	{
		aiFace face = _mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	//ボーンデータ初期化
	for (unsigned int b = 0; b < _mesh->mNumBones; b++)
	{
		// メッシュに関連づいてるボーン情報を取得
		aiBone* bone = _mesh->mBones[b];

		// ボーンオフセット行列を取得
		const int matrixNum = 4;
		for (int i = 0; i < matrixNum; i++) {
			for (int j = 0; j < matrixNum; j++) {
				m_bone[bone->mName.C_Str()].offsetMatrix.m[i][j] = bone->mOffsetMatrix[i][j];
			}
		}

		// ボーンに関連づいている頂点を選び､ウェイト値をセットする
		//for (unsigned int widx = 0; widx < bone->mNumWeights; widx++)
		//{
		//	aiVertexWeight weight = bone->mWeights[widx];

		//	unsigned int vidx = weight.mVertexId;			// このウエイトに関連づいてる頂点idx

		//													// メッシュの中の何番目か
		//	vertices[vidx].boneWeight[vertices[vidx].boneNum] = weight.mWeight;
		//	// vertices[vidx].m_BoneName[vertices[vidx].boneNum] = bone->mName.C_Str();
		//	// 該当するボーン名のインデックス値をセット
		//	vertices[vidx].boneIndex[vertices[vidx].boneNum] = m_bone[bone->mName.C_Str()].idx;

		//	vertices[vidx].boneNum++;

		//	assert(vertices[vidx].boneNum <= 4);
		//}
	}

	// テクスチャ情報を取得する
	if (_mesh->mMaterialIndex >= 0)
	{
		// このメッシュのマテリアルインデックス値を取得する
		int	mtrlidx = _mesh->mMaterialIndex;

		// シーンからマテリアルデータを取得する
		aiMaterial* material = _scene->mMaterials[mtrlidx];

		// このマテリアルに関連づいたテクスチャを取り出す
		LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", _scene);

	}

	newMesh->Load(vertices, indices);
	
	return newMesh;
	// return Mesh(vertices, indices, textures);

}

void ModelData::UpdateBoneMatrix(aiNode* node,math::Matrix _mat) {
	Bone* bone = &m_bone[node->mName.C_Str()];

	//マトリクスの乗算順番に注意
	//（親ボーンとの相対位置を示す行列＊ボーン行列＊ボーンオフセット行列）
	math::Matrix worldMatrix;
	// 
	/*
	TReal a1, a2, a3, a4;   // assimp 行列は、行優先
	TReal b1, b2, b3, b4;
	TReal c1, c2, c3, c4;
	TReal d1, d2, d3, d4;
	*/

	worldMatrix = _mat;
	worldMatrix *= bone->animationMatrix;

	bone->matrix = worldMatrix;
	bone->matrix *= bone->offsetMatrix;

	for (unsigned int n = 0; n < node->mNumChildren; n++)
	{
		UpdateBoneMatrix(node->mChildren[n], worldMatrix);
	}
}

void ModelData::LoadMaterialTextures(aiMaterial * _mat, aiTextureType _type, std::string typeName, const aiScene * scene) {
	// マテリアルからテクスチャ個数を取得し(基本は1個)ループする
	for (unsigned int i = 0; i < _mat->GetTextureCount(_type); i++)
	{
		aiString str;
		std::string texFileName;
		texFileName = str.C_Str();

		// マテリアルからｉ番目のテクスチャファイル名を取得する
		_mat->GetTexture(_type, i, &str);

		for (auto &itr : m_texture) {
			itr.Load(texFileName);
		}
	}

	return;
}

}  // namespace render
}  // namespace mslib
