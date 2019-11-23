#pragma once
#include "./core/Object/Object.h"

namespace mslib {
namespace component {

class BaseLightComponent;
using BaseLightComponentPtr = std::weak_ptr<BaseLightComponent>;
using BaseLightComponentSPtr = std::shared_ptr<BaseLightComponent>;

class BaseLightComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	BaseLightComponent() { m_color = math::Vector4(1.f, 1.f, 1.f, 1.f); };
	virtual ~BaseLightComponent() = default;

	virtual void Initialize() override {};
	virtual void Update() override;

private:
	math::Vector4 m_color;
};

}
}