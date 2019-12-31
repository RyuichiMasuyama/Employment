#include "./ModelRenderComponent.h"


namespace mslib {
namespace component {
void ModelRenderComponent::FixedUpdate() {
	if (!m_after)
		render::Render::GetInstance().Draw(m_transform.lock()->m_matrix, m_model);
	else
		render::Render::GetInstance().AfterDraw(m_transform.lock()->m_matrix, m_model);
}
void ModelRenderComponent::AfterFlagOn()
{
	m_after = true;
}
}
}