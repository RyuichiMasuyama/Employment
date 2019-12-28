#pragma once

#include "./Math/Vector.h"

#include "./Renderer/RenderObject.h"

namespace mslib {
namespace Primitive {
class Primitive :public render::MyMesh {
public:
	Primitive() {
		m_memberMaterial = &m_material;
		//m_polygons = std::make_shared<render::Polygons>();
	}
	~Primitive() = default;

protected:
	std::vector<std::shared_ptr<render::Material>>* m_memberMaterial;

	void Set() {
		GetPipeline()->CreateIndexBuffer(GetPolygons()->index.size(), &GetPolygons()->index[0]);
		GetPipeline()->CreateVertexBuffer(sizeof(GetPolygons()->vertex[0]), GetPolygons()->vertex.size(), &GetPolygons()->vertex.at(0));

		for (auto itr : m_material[0]->textureName) {
			GetPipeline()->LoadTexture(itr);
		}
		// �V�F�[�_�[���[�h
		GetPipeline()->SetVertexPixcle(
			m_material[0]->shaderName[static_cast<int>(render::SHADER_ENUM::VERTEX_SHADER)],
			m_material[0]->shaderName[static_cast<int>(render::SHADER_ENUM::PIXEL_SHADER)]
		);
		GetPipeline()->SetGeometory(m_material[0]->shaderName[static_cast<int>(render::SHADER_ENUM::GEOMETRY_SHADER)]);
		GetPipeline()->SetHullDomainShader(
			m_material[0]->shaderName[static_cast<int>(render::SHADER_ENUM::HULL_SHADER)],
			m_material[0]->shaderName[static_cast<int>(render::SHADER_ENUM::DOMAIN_SHADER)]
		);
	}
};

class QuadPrimitive :public Primitive {
public:
	QuadPrimitive() {
		render::PolygonAnimationVertex model[]{
			{ math::Vector3(-1.f,1.f,0.f),math::Vector3(0.f,0.f,-1.f) ,math::Vector2(0.f,0.f) },
			{ math::Vector3(1.f,1.f,0.f),math::Vector3(0.f,0.f,-1.f)  ,math::Vector2(1.f,0.f) },
			{ math::Vector3(-1.f,-1.f,0.f),math::Vector3(0.f,0.f,-1.f) ,math::Vector2(0.f,1.f) },
			{ math::Vector3(1.f,-1.f,0.f),math::Vector3(0.f,0.f,-1.f)  ,math::Vector2(1.f,1.f) },
		};

		int index[]{
			0,1,2,1,3,2
		};

		render::Material mat{
			math::Vector3(0.1f, 0.1f, 0.1f),		//�A���r�G���g
			math::Vector3(0.8f, 0.8f, 0.8f),		//�f�B�t���[�Y
			math::Vector3(0.f, 0.f, 0.f),			//�G�~�b�V�u
			math::Vector3(0.f, 0.f, 0.f),			//�o���v
			0.8f,									//�g�����X�y�A�����g
			math::Vector4(0.2f, 0.2f, 0.2f, 0.9f),	//�X�y�L����(w=Power)
			0.5f,									//�V���C�j�[�Y
			0.5f,									//���t���N�V����
		};
		mat.shaderName[static_cast<int>(render::SHADER_ENUM::VERTEX_SHADER)] = "shader/base/vsRender2DBase.fx";
		mat.shaderName[static_cast<int>(render::SHADER_ENUM::PIXEL_SHADER)] = "shader/base/psRender2DBase.fx";

		for (auto itr : model)
			GetPolygons()->vertex.push_back(itr);
		for (auto itr : index)
			GetPolygons()->index.push_back(itr);
		m_memberMaterial->push_back(std::make_shared < render::Material >(mat));

		Set();
	};
};
}
}