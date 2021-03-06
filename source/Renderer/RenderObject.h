#pragma once
#include "./MyDirectXMath.h"
#include <string>
#include <vector>
#include <array>

#ifdef DIRECTX11
#include "./DirectX/DirectXPipeline.h"
#endif

#ifdef DIRECTX11
namespace mslib {
namespace directx {
class DirectXPipeline;
}
}
#endif

namespace mslib {
namespace Primitive {
class Primitive;
}
}

namespace mslib {
namespace render {

using Pipeline = directx::DirectXPipeline;

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

enum class TEXTURE_ENUM {
	TEXTURE,
	TEXTURE_NORMAL,
	TEXTURE_BUMP,
	MAX
};

enum class SHADER_ENUM {
	VERTEX_SHADER,
	PIXEL_SHADER,
	GEOMETRY_SHADER,
	HULL_SHADER,
	DOMAIN_SHADER,
	MAX
};

struct Material {
	math::Vector3 ambient = math::Vector3(0.1f, 0.1f, 0.1f);		//アンビエント
	math::Vector3 diffuse = math::Vector3(0.8f, 0.8f, 0.8f);		//ディフューズ
	math::Vector3 emissive = math::Vector3(0.f, 0.f, 0.f);		//エミッシブ
	math::Vector3 bump;			//バンプ
	float transparency;			//トランスペアレント
	math::Vector4 specular = math::Vector4(0.2f, 0.2f, 0.2f, 0.9f);		//スペキュラ(w=Power)
	float shininess;			//シャイニーズ
	float reflectivity;			//リフレクション

	// 各種シェーダーの名前
	// 何もなければnullを選択
	// 今後モデルデータにも追加
	std::array<std::string, static_cast<int>(SHADER_ENUM::MAX)> shaderName;
	std::array<std::string, static_cast<int>(TEXTURE_ENUM::MAX)> textureName;
};

struct Polygons {
	//頂点データ
	std::vector<Vertex3DModel>	vertex;

	//法線データ
	//std::vector<Vector3>	normal;

	//インデックスデータ
	std::vector<UINT>	index;
};

class MyMesh {
	friend Primitive::Primitive;
private:
	//Materialデータ
	std::vector<Material>	m_material;

	//ポリゴンデータ
	Polygons	m_polygons;

	// render用のパインライン
	Pipeline m_pipeline;
public:
	MyMesh();

	const std::vector<Material>&  GetMaterial();

	Material * GetMaterial(int num);

	Polygons * GetPolygons();

	Pipeline * GetPipeline();

	void Load(std::string _file_name);

};

}
}