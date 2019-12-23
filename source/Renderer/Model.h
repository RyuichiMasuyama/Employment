#pragma once

#include "./Mesh.h"
#include "./RenderObject.h"
#include "../AssetManager/TextureLoader.h"
#include "../Shader/Shader.h"

namespace mslib {
namespace render {
class ModelData {
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	ModelData() = default;
	~ModelData() = default;

	void Load();

	// �`��
	void Draw();

	// �V�F�[�_�̃Z�b�g
	void SetTexture(texture::Texture _texture);

	// �e��V�F�[�_�̃Z�b�g
	void SetVertexShader(shader::VertexShader _shader);
	void SetPixelShader(shader::PixelShader _shader);
	void SetGeometryShader(shader::GeometryShader _shader);
	void SetHullShader(shader::HullShader _shader);
	void SetDomainShader(shader::DomainShader _shader);
private:
	// ���b�V�����
	std::vector<std::shared_ptr<Mesh>> m_meshs;
	// �}�e���A��
	std::shared_ptr<Material> m_material;
	// �V�F�[�_�[(�����ŃX�}�[�g�|�C���^�ɂ��Ă���)
	shader::ShaderResource m_shaders;
};
}
}