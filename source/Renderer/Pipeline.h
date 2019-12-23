#pragma once

#include "RenderObject.h"

#ifdef DIRECTX11
#include "./DirectX/DirectXPipeline.h"
#endif

namespace mslib {
namespace render {

class Pipeline :public directx::DirectXPipeline {
public:
	Pipeline();
	~Pipeline();

private:
	// �Q�Ƃ��郍�[�h���ꂽ���b�V��
	std::shared_ptr<MyMesh> m_mesh;

	// ���ۂɎg���|���S�����f��
	std::shared_ptr<Polygons> m_polygon;
	
	// ���ۂɎg���}�e���A��
	std::shared_ptr<Material> m_material;

	shader::InputLayer m_inputLayer;
	shader::PixelShader m_pixelShader;
	shader::VertexShader m_vertexShader;
	shader::GeometryShader m_geometryShader;
	shader::DomainShader m_domainShader;
	shader::HullShader m_hullShader;

public:
	void Draw();
};

}
}