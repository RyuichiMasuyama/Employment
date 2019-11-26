#pragma once
#include "./MyDirectXMath.h"
#include <string>
#include <vector>

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

enum TEXTURE_ENUM {
	TEXTURE,
	TEXTURE_NORMAL,
	TEXTURE_BUMP,
	TEXTURE_MAX
};

struct Material {
	math::Vector3 ambient;		//アンビエント
	math::Vector3 diffuse;		//ディフューズ
	math::Vector3 emissive;		//エミッシブ
	math::Vector3 bump;			//バンプ
	float transparency;			//トランスペアレント
	math::Vector4 specular;		//スペキュラ(w=Power)
	float shininess;			//シャイニーズ
	float reflectivity;			//リフレクション

	// 各種シェーダーの名前
	// 何もなければnullを選択
	// 今後モデルデータにも追加
	std::string vsName = "null";
	std::string psName = "null";
	std::string gsName = "null";
	std::string hsName = "null";
	std::string dsName = "null";

	std::vector<std::string>	textureName;
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
private:
	//Materialデータ
	Material	m_material;

	//ポリゴンデータ
	Polygons	m_polygons;

	// render用のパインライン
	Pipeline m_pipeline;
public:
	MyMesh();

	Material * GetMaterial();

	Polygons * GetPolygons();

	Pipeline * GetPipeline();

	void Load(std::string _file_name);

};

}
}