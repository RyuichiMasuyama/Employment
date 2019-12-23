#include "RenderComponent.h"
#include "./Renderer/RenderObject.h"
#include "./AssetManager/TextureLoader.h"

namespace mslib {
namespace component {

void RenderComponent::FixedUpdate() {
	render::Render::GetInstance().Draw(m_transform.lock()->m_matrix, m_mesh.GetPipeline());
}

void RenderComponent::SetShader(std::string _shaderName, shader::ShaderType _shaderType) {
	m_mesh.SetShader(_shaderName, _shaderType);
}

void RenderComponent::SetTexture(std::string _textureName, int _number) {
	m_mesh.SetTexture(_textureName, _number);
}

}
}