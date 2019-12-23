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
	// 各種バッファ
	VertexBuffer m_vertex_buffer;
	IndexBuffer m_index_buffer;

	// シェーダ
	shader::ShaderResource m_shaderResource;

	// テクスチャ
	std::vector<texture::Texture> m_texture;
	
	// メッシュ
	render::MyMesh* m_mesh;
public:
	// コンストラクタ
	// 生成される時に
	DirectXPipeline(render::MyMesh* _mesh) :m_mesh(_mesh) {};
	~DirectXPipeline() = default;

	//その他シェーダーの設定
	void SetVertexShader(std::string	_vs);
	void SetPixelShader(std::string		_ps);
	void SetVertexPixcle(std::string	_vs, std::string		_ps);
	void SetGeometory(std::string	_gs);
	void SetHullDomainShader(std::string	_ds, std::string	_hs);
	void SetHullShader(std::string	_hs);
	void SetDomainShader(std::string	_ds);

	// テクスチャの設定
	void SetTexture(texture::Texture _texture,int _setNumber);

	void LoadTexture(std::string _textureName);

	// 描画
	void Draw();
	// シェーダの設定をしない描画()
	void NoSetShaderDraw();

	// 各種バッファ生成関数
	void CreateVertexBuffer(size_t _vertexSize, size_t _vertexNum, void *_vertexFrontAddress);
	void CreateIndexBuffer(size_t _indexNum, void* _indexFrontAddress);
};
}
}