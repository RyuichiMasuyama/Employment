#include "./BaseLightComponent.h"
#include "./MyDirectXTransform.h"

namespace mslib {
namespace component {

void BaseLightComponent::Update() {
	auto wayVec4 = math::Vector4(m_transform.lock()->m_matrix.GetUp());

	directx::SubResourceSendManager::GetInstance().SetLightBuffer(wayVec4, m_color);
}


}
}
