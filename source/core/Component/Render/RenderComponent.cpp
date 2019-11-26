#include "RenderComponent.h"
#include "./Renderer/RenderObject.h"

namespace mslib {
namespace component {

void RenderComponent::FixedUpdate() {
	render::Render::GetInstance().Draw(m_transform.lock()->m_matrix, m_mesh.lock()->GetPipeline());
}

}
}