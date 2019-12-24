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
	// �R���X�g���N�^�E�f�X�g���N�^
	ModelData() = default;
	~ModelData() = default;

	// ���f���̃��[�h
	void Load(std::string _fileName);
	// �`��
	void Draw();

	void AnimationUpdate(unsigned int _animeNo,unsigned int _animeFileNo);

	// �V�F�[�_�̃Z�b�g
	void SetTexture(texture::Texture _texture, int _number);

	// �e��V�F�[�_�̃Z�b�g
	void SetVertexShader(std::string _shadeName);
	void SetPixelShader(std::string _shadeName);
	void SetGeometryShader(std::string _shadeName);
	void SetHullShader(std::string _shadeName);
	void SetDomainShader(std::string _shadeName);
private:
	// ���b�V�����
	std::vector<std::shared_ptr<Mesh>> m_meshs;
	// �}�e���A��
	std::shared_ptr<Material> m_material;
	// �V�F�[�_�[(�����ŃX�}�[�g�|�C���^�ɂ��Ă���)
	shader::Shaders m_shaders;
	// �e�N�X�`��
	std::array< texture::Texture, TEXTURE_MAX > m_texture;
	// �{�[���f�[�^
	std::map<std::string, render::Bone> m_bone;
	// �A�V���v����
	// �����ɂ���̂͂悭�Ȃ�
	assimp::AssimpScene m_assimpScene;

	// �L�[�t���[���A�j���[�V�����f�[�^
	int m_Frame = 0;							// �t���[���ԍ�
	int m_cnt = 0;								// �L�[�t���[����ԗp
	int m_preFrame = 0;							// �L�[�t���[����ԗp
	float m_factor = 0.0f;						// �L�[�t���[����ԗp

	// �A�V���v�⏕�֐�
	// �{�[�����̉�͂ƕێ�
	void CreateBone(aiNode* node);
	// �m�[�h�̉��
	void ProcessNode(aiNode* _node, const aiScene* _scene);
	// ���b�V�������
	std::shared_ptr<Mesh> ProcessMesh(aiMesh* _mesh, const aiScene* _scene, unsigned int _meshidx);
	// �ċA�I�Ƀ{�[���X�V
	void UpdateBoneMatrix(aiNode* node, math::Matrix _mat);
	void LoadMaterialTextures(
		aiMaterial * _mat,
		aiTextureType _type,
		std::string _typeName,
		const aiScene * _scene);

};
}
}