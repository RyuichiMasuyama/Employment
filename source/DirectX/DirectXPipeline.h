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
	VertexBuffer m_vertex_buffer;
	IndexBuffer m_index_buffer;
	shader::ShaderResource m_shaderResource;

	std::vector<texture::Texture> m_texture;
	
	render::MyMesh* m_mesh;
public:
	DirectXPipeline(render::MyMesh* _mesh) :m_mesh(_mesh) {};
	~DirectXPipeline() = default;

	//その他シェーダーの設定
	void SetVertexPixcle(std::string	_vs,std::string		_ps);
	void SetGeometory(std::string	_gs);
	void SetHullDomainShader(std::string	_ds, std::string	_hs);

	void SetTexture(texture::Texture _texture,int _setNumber);

	void Draw();
	void NoSetShaderDraw();

	void CreateVertexBuffer(size_t _vertexSize, size_t _vertexNum, void *_vertexFrontAddress);
	void CreateIndexBuffer(size_t _indexNum, void* _indexFrontAddress);

	void LoadTexture(std::string _textureName);
};
}
}