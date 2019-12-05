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

//���_�f�[�^2D
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

//���_�f�[�^3D
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

//�{�[���f�[�^
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
	math::Vector3 ambient = math::Vector3(0.1f, 0.1f, 0.1f);		//�A���r�G���g
	math::Vector3 diffuse = math::Vector3(0.8f, 0.8f, 0.8f);		//�f�B�t���[�Y
	math::Vector3 emissive = math::Vector3(0.f, 0.f, 0.f);		//�G�~�b�V�u
	math::Vector3 bump;			//�o���v
	float transparency;			//�g�����X�y�A�����g
	math::Vector4 specular = math::Vector4(0.2f, 0.2f, 0.2f, 0.9f);		//�X�y�L����(w=Power)
	float shininess;			//�V���C�j�[�Y
	float reflectivity;			//���t���N�V����

	// �e��V�F�[�_�[�̖��O
	// �����Ȃ����null��I��
	// ���ヂ�f���f�[�^�ɂ��ǉ�
	std::string vsName = "null";
	std::string psName = "null";
	std::string gsName = "null";
	std::string hsName = "null";
	std::string dsName = "null";

	std::vector<std::string>	textureName;
};

struct Polygons {
	//���_�f�[�^
	std::vector<Vertex3DModel>	vertex;

	//�@���f�[�^
	//std::vector<Vector3>	normal;

	//�C���f�b�N�X�f�[�^
	std::vector<UINT>	index;
};

class MyMesh {
private:
	//Material�f�[�^
	Material	m_material;

	//�|���S���f�[�^
	Polygons	m_polygons;

	// render�p�̃p�C�����C��
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