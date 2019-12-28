#include "./Model.h"
#include "./AssetManager/TextureLoader.h"
#include "./AssetManager/ShaderLoader.h"

namespace mslib {
namespace render {
void ModelData::Load(std::string _fileName) {
	bool sts = m_assimpScene.Init(_fileName);

	// m_directory = resourcefolder;		// ���̃��f���̃e�N�X�`�������݂���f�B���N�g��

	// �{�[���𐶐�����
	CreateBone(m_assimpScene.GetScene()->mRootNode);

	// �{�[���̔z��ʒu���i�[����
	unsigned int num = 0;
	for (auto& itr : m_bone) {
		itr.second.idx = num;
		num++;
	}
	// ai�m�[�h����͂���
	ProcessNode(m_assimpScene.GetScene()->mRootNode, m_assimpScene.GetScene());
	//auto mesh = std::make_shared< render::Mesh >();

	//std::vector<PolygonAnimationVertex> vertices;			// ���_
	//std::vector<PolygonIndex> indices;		// �ʂ̍\�����
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
	// 0�Ԗڂ̃V�[�������o��
	const aiScene* scene = m_assimpScene.GetScene();

	// �A�j���[�V�����f�[�^�������Ă��邩�H
	if (scene->HasAnimations())
	{
		//�A�j���[�V�����f�[�^����{�[���}�g���N�X�Z�o
		aiAnimation* animation = scene->mAnimations[_animeNo];

		// �{�[���̐��������[�v
		for (unsigned int c = 0; c < animation->mNumChannels; c++)
		{
			aiNodeAnim* nodeAnim = animation->mChannels[c];

			// �{�[�����݃`�F�b�N(�A�j���[�V�����ɂ̂ݑ��݂���{�[�����������ꍇ�͖�������)
			auto itr = m_bone.find(nodeAnim->mNodeName.C_Str());
			if (itr != m_bone.end()) {
				Bone* bone = &m_bone[nodeAnim->mNodeName.C_Str()];

				int f1, f2;

				f1 = m_Frame % nodeAnim->mNumRotationKeys;//�ȈՎ���   
				aiQuaternion rot1 = nodeAnim->mRotationKeys[f1].mValue; // �N�I�[�^�j�I��

				f1 = m_Frame % nodeAnim->mNumPositionKeys;//�ȈՎ���
				aiVector3D pos1 = nodeAnim->mPositionKeys[f1].mValue;

				f2 = m_preFrame % nodeAnim->mNumRotationKeys;//�ȈՎ���  
				aiQuaternion rot2 = nodeAnim->mRotationKeys[f2].mValue; // �N�I�[�^�j�I��

				f2 = m_preFrame % nodeAnim->mNumPositionKeys;//�ȈՎ���	
				aiVector3D pos2 = nodeAnim->mPositionKeys[f2].mValue;

				// ���
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

		//�ċA�I�Ƀ{�[���}�g���N�X���X�V
		UpdateBoneMatrix(m_assimpScene.GetScene()->mRootNode, math::Matrix());

		// ���b�V����OBB�X�V
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

	// �m�[�h�����L�[�ɂ��ă{�[������ۑ�
	m_bone[node->mName.C_Str()] = bone;

	for (unsigned int n = 0; n < node->mNumChildren; n++)
	{
		CreateBone(node->mChildren[n]);
	}
}

void ModelData::ProcessNode(aiNode * _node, const aiScene * _scene) {
	// �m�[�h���̃��b�V���̐������[�v����
	for (unsigned int i = 0; i < _node->mNumMeshes; i++)
	{
		int meshIndex = _node->mMeshes[i];			// �m�[�h��i�Ԗڃ��b�V���̃C���f�b�N�X���擾
		aiMesh* mesh = _scene->mMeshes[meshIndex];	// �V�[�����烁�b�V���{�̂����o��

		m_meshs.push_back(this->ProcessMesh(mesh, _scene, meshIndex));
	}

	// �q�m�[�h�ɂ��Ă����
	for (unsigned int i = 0; i < _node->mNumChildren; i++)
	{
		// �ċA���Ȃ̂ňꉞ���N���X�Ǝ������߂�this�|�C���^�Q��
		this->ProcessNode(_node->mChildren[i], _scene);
	}
}

std::shared_ptr< Mesh > ModelData::ProcessMesh(aiMesh * _mesh, const aiScene * _scene, unsigned int _meshidx) {
	auto newMesh = std::make_shared<Mesh>();
	std::vector<PolygonAnimationVertex> vertices;			// ���_
	std::vector<PolygonIndex> indices;		// �ʂ̍\�����
	// std::vector<Texture> textures;			// �e�N�X�`��
	
	// ���_�����擾
	for (unsigned int i = 0; i < _mesh->mNumVertices; i++)
	{
		PolygonAnimationVertex vertex;

		vertex.pos.x = _mesh->mVertices[i].x;
		vertex.pos.y = _mesh->mVertices[i].y;
		vertex.pos.z = _mesh->mVertices[i].z;

		// �@���x�N�g�������݂��邩�H
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

		// �e�N�X�`�����W�i�O�Ԗځj�����݂��邩�H
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

	// �ʂ̍\�������擾
	for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
	{
		aiFace face = _mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	//�{�[���f�[�^������
	for (unsigned int b = 0; b < _mesh->mNumBones; b++)
	{
		// ���b�V���Ɋ֘A�Â��Ă�{�[�������擾
		aiBone* bone = _mesh->mBones[b];

		// �{�[���I�t�Z�b�g�s����擾
		const int matrixNum = 4;
		for (int i = 0; i < matrixNum; i++) {
			for (int j = 0; j < matrixNum; j++) {
				m_bone[bone->mName.C_Str()].offsetMatrix.m[i][j] = bone->mOffsetMatrix[i][j];
			}
		}

		// �{�[���Ɋ֘A�Â��Ă��钸�_��I�Ѥ�E�F�C�g�l���Z�b�g����
		//for (unsigned int widx = 0; widx < bone->mNumWeights; widx++)
		//{
		//	aiVertexWeight weight = bone->mWeights[widx];

		//	unsigned int vidx = weight.mVertexId;			// ���̃E�G�C�g�Ɋ֘A�Â��Ă钸�_idx

		//													// ���b�V���̒��̉��Ԗڂ�
		//	vertices[vidx].boneWeight[vertices[vidx].boneNum] = weight.mWeight;
		//	// vertices[vidx].m_BoneName[vertices[vidx].boneNum] = bone->mName.C_Str();
		//	// �Y������{�[�����̃C���f�b�N�X�l���Z�b�g
		//	vertices[vidx].boneIndex[vertices[vidx].boneNum] = m_bone[bone->mName.C_Str()].idx;

		//	vertices[vidx].boneNum++;

		//	assert(vertices[vidx].boneNum <= 4);
		//}
	}

	// �e�N�X�`�������擾����
	if (_mesh->mMaterialIndex >= 0)
	{
		// ���̃��b�V���̃}�e���A���C���f�b�N�X�l���擾����
		int	mtrlidx = _mesh->mMaterialIndex;

		// �V�[������}�e���A���f�[�^���擾����
		aiMaterial* material = _scene->mMaterials[mtrlidx];

		// ���̃}�e���A���Ɋ֘A�Â����e�N�X�`�������o��
		LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", _scene);

	}

	newMesh->Load(vertices, indices);
	
	return newMesh;
	// return Mesh(vertices, indices, textures);

}

void ModelData::UpdateBoneMatrix(aiNode* node,math::Matrix _mat) {
	Bone* bone = &m_bone[node->mName.C_Str()];

	//�}�g���N�X�̏�Z���Ԃɒ���
	//�i�e�{�[���Ƃ̑��Έʒu�������s�񁖃{�[���s�񁖃{�[���I�t�Z�b�g�s��j
	math::Matrix worldMatrix;
	// 
	/*
	TReal a1, a2, a3, a4;   // assimp �s��́A�s�D��
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
	// �}�e���A������e�N�X�`�������擾��(��{��1��)���[�v����
	for (unsigned int i = 0; i < _mat->GetTextureCount(_type); i++)
	{
		aiString str;
		std::string texFileName;
		texFileName = str.C_Str();

		// �}�e���A�����炉�Ԗڂ̃e�N�X�`���t�@�C�������擾����
		_mat->GetTexture(_type, i, &str);

		for (auto &itr : m_texture) {
			itr.Load(texFileName);
		}
	}

	return;
}

}  // namespace render
}  // namespace mslib
