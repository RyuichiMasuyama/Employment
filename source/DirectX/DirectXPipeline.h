#pragma once

#include "./DirectX/DirectX11Manager.h"
#include "./Shader/Shader.h"
#include "./AssetManager/TextureLoader.h"

namespace mslib {
namespace render{
class MyMesh;
}
namespace directx {
class DirectXPipeline {
	friend class DirectXPostEffect;
private:
	// �e��o�b�t�@
	VertexBuffer m_vertex_buffer;
	IndexBuffer m_index_buffer;

	// �V�F�[�_
	shader::ShaderResource m_shaderResource;

	// �e�N�X�`��
	std::vector<texture::Texture> m_texture;
	
	// ���b�V��
	render::MyMesh* m_mesh;
public:
	// �R���X�g���N�^
	// ��������鎞��
	DirectXPipeline(render::MyMesh* _mesh) :m_mesh(_mesh) {};
	~DirectXPipeline() = default;

	//���̑��V�F�[�_�[�̐ݒ�
	void SetVertexShader(std::string	_vs);
	void SetPixelShader(std::string		_ps);
	void SetVertexPixcle(std::string	_vs, std::string		_ps);
	void SetGeometory(std::string	_gs);
	void SetHullDomainShader(std::string	_ds, std::string	_hs);
	void SetHullShader(std::string	_hs);
	void SetDomainShader(std::string	_ds);

	// �e�N�X�`���̐ݒ�
	void SetTexture(texture::Texture _texture,int _setNumber);

	void LoadTexture(std::string _textureName);

	// �`��
	void Draw();
	// �V�F�[�_�̐ݒ�����Ȃ��`��()
	void NoSetShaderDraw();

	// �e��o�b�t�@�����֐�
	void CreateVertexBuffer(size_t _vertexSize, size_t _vertexNum, void *_vertexFrontAddress);
	void CreateIndexBuffer(size_t _indexNum, void* _indexFrontAddress);
};
}
}