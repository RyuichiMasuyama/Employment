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
	// 参照するロードされたメッシュ
	std::shared_ptr<MyMesh> m_mesh;

	// 実際に使うポリゴンモデル
	std::shared_ptr<Polygons> m_polygon;
	
	// 実際に使うマテリアル
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