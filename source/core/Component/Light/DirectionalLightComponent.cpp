#include "./DirectionalLightComponent.h"
#include "./DirectX/SubResourceSendManager.h"

namespace mslib {
namespace component {
DirectionalLightComponent::DirectionalLightComponent() {
	SetMyLightType(LIGHT_TYPE::DIRECTIONAL);
}
void DirectionalLightComponent::FixedUpdate() {
	auto wayVec4 = math::Vector4(m_transform.lock()->m_matrix.GetFront());

	//���b�s���O����ƈႤ�֐��ɂȂ� 
	directx::SubResourceSendManager::GetInstance().SetLightBuffer(wayVec4, m_color);
}

}
}
