#include "./BaseLightComponent.h"

#include "./DirectX/SubResourceSendManager.h"

namespace mslib {
namespace component {

void BaseLightComponent::SetMyLightType(LIGHT_TYPE _lightType) {
	m_myType = _lightType;
}

void BaseLightComponent::SetColor(math::Vector3 _color) {
	m_color = _color;
}

void BaseLightComponent::SetPower(float _power) {
	m_color.w = _power;
}
}
}
