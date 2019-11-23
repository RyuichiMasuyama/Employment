#pragma once
#include "MyDirectXMath.h"
#include "./Shader/Shader.h"

namespace mslib {
namespace render {

//頂点データ2D
struct Vertex2D
{
	math::Vector2 pos;
	math::Vector2 uv;
	math::Vector4 color;
};

struct TestVertex2D
{
	math::Vector3 pos;
	math::Vector4 color;
};

//頂点データ3D
struct Vertex3D
{
	math::Vector3 pos;
	math::Vector3 uv;
	math::Vector4 color;
};

struct Vertex3DModel {
	math::Vector3 pos;
	math::Vector3 normal;
	math::Vector3 tangent;
	math::Vector2 uv;
};

//ボーンデータ
struct VertexBone
{
	math::Vector3 pos;
};

enum TEXTURE_ENUM {
	TEXTURE,
	TEXTURE_NORMAL,
	TEXTURE_BUMP,
	TEXTURE_MAX
};

struct Material
{
	math::Vector3 ambient;		//アンビエント
	math::Vector3 diffuse;		//ディフューズ
	math::Vector3 emissive;		//エミッシブ
	math::Vector3 bump;			//バンプ
	float transparency;		//トランスペアレント
	math::Vector3 specular;		//スペキュラ
	float specular_power;	//スペキュラパワー
	float shininess;		//シャイニーズ
	float reflectivity;		//リフレクション

	std::vector<std::string> texture_name;
	std::vector<mslib::directx::ShaderTexture> texture;
};

struct Polygons {

	//頂点データ
	std::vector<Vertex3DModel>	vertex;

	//法線データ
	//std::vector<Vector3>	normal;

	//インデックスデータ
	std::vector<UINT>		index;

};

class MyMesh {
private:
	//Materialデータ
	Material	m_material;

	//ポリゴンデータ
	Polygons	m_polygons;

	//シェーダデータ
	shader::ShaderResource m_shader_resource;

public:
	MyMesh();

	Material * GetMaterial();

	Polygons * GetPolygons();

	shader::ShaderResource* GetShaderResource();

	void Load(std::string _file_name);
};

}
}