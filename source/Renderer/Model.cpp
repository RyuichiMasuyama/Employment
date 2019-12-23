#include "Model.h"

namespace mslib {
namespace render {

void ModelData::Draw() {
	for (auto& itr : m_meshs) {
		itr->Draw();
	}
}

void ModelData::SetVertexShader(shader::VertexShader _shader) {
	m_shaders.vertexShader = _shader;
}

void ModelData::SetPixelShader(shader::PixelShader _shader) {
	m_shaders.pixelShader = _shader;
}

void ModelData::SetGeometryShader(shader::GeometryShader _shader) {
	m_shaders.geometryShader = _shader;
}

void ModelData::SetHullShader(shader::HullShader _shader) {
	m_shaders.hullShader = _shader;
}

void ModelData::SetDomainShader(shader::DomainShader _shader) {
	m_shaders.domainShader = _shader;
}

}  // namespace render
}  // namespace mslib
