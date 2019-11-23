#pragma once
#include "MyDirectXMath.h"
#include "./Shader/Shader.h"

namespace mslib {
namespace render {

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

struct Material
{
	math::Vector3 ambient;		//�A���r�G���g
	math::Vector3 diffuse;		//�f�B�t���[�Y
	math::Vector3 emissive;		//�G�~�b�V�u
	math::Vector3 bump;			//�o���v
	float transparency;		//�g�����X�y�A�����g
	math::Vector3 specular;		//�X�y�L����
	float specular_power;	//�X�y�L�����p���[
	float shininess;		//�V���C�j�[�Y
	float reflectivity;		//���t���N�V����

	std::vector<std::string> texture_name;
	std::vector<mslib::directx::ShaderTexture> texture;
};

struct Polygons {

	//���_�f�[�^
	std::vector<Vertex3DModel>	vertex;

	//�@���f�[�^
	//std::vector<Vector3>	normal;

	//�C���f�b�N�X�f�[�^
	std::vector<UINT>		index;

};

class MyMesh {
private:
	//Material�f�[�^
	Material	m_material;

	//�|���S���f�[�^
	Polygons	m_polygons;

	//�V�F�[�_�f�[�^
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