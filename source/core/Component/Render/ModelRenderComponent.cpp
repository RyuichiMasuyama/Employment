#include "./ModelRenderComponent.h"


namespace mslib {
namespace component {
void ModelRenderComponent::FixedUpdate() {
	render::Render::GetInstance().Draw(m_transform.lock()->m_matrix, m_model.GetPipeline());
}
}
}