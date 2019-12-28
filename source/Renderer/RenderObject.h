#pragma once
#include "./MyDirectXMath.h"
#include <string>
#include <vector>
#include <array>


#include "./BaseMesh.h"
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
	std::array<std::string, static_cast<int>(SHADER_ENUM::MAX)> shaderName;
	std::array<std::string, static_cast<int>(TEXTURE_ENUM::MAX)> textureName;
};

struct Polygons {
	//���_�f�[�^
	std::vector<PolygonAnimationVertex>	vertex;

	//�@���f�[�^
	//std::vector<Vector3>	normal;

	//�C���f�b�N�X�f�[�^
	std::vector<UINT>	index;
};

// ���b�V����Material�Ƃ��e�N�X�`�����������邠��p�C�v���C����
// �ێ����Ȃ���΂����Ȃ��悤�ȏ󋵂ɂȂ��Ă��܂��Ă���
class MyMesh {
	friend Primitive::Primitive;
private:
	//Material�f�[�^
	std::vector<std::shared_ptr<Material>>	m_material;

	//�|���S���f�[�^
	std::shared_ptr<Polygons>	m_polygons;

	// render�p�̃p�C�����C��
	Pipeline m_pipeline;
public:
	MyMesh();

	const std::vector<std::shared_ptr<Material>>&  GetMaterial();

	// Material��shared��n��
	// ������Material�̐���蒴����������v���������AnullWeak���A���Ă���
	std::shared_ptr<Material> GetMaterial(int num);

	// �|���S�����擾����
	std::shared_ptr<Polygons> GetPolygons();

	// void SetMaterial();
	// ���b�V���ɐݒ肳��Ă���V�F�[�_�[���玩���Őݒ�
	void SetShader(std::string _shaderName, shader::ShaderType _shaderType);

	// ���b�V���ɐݒ肳��Ă���e�N�X�`�����玩���Őݒ�
	void SetTexture(std::string _textureName, int textureNumber);

	// �����_�����O�p�Ƀp�C�v���C�����擾(�Y�킶��Ȃ�����ύX����)
	Pipeline * GetPipeline();
	
	// �����̃��f�����Z�b�g
	void Load(std::string _file_name);
};
}
}