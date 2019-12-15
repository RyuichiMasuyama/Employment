#pragma once
#include "./core/Object/Object.h"
#include "../../Camera/base/BaseCameraComponent.h"

namespace mslib {
enum class LIGHT_TYPE;
enum class LIGHT_TYPE {
	DIRECTIONAL,
	POINT,
	SPOT,
};
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

	void SetColor(math::Vector3 _color);
	void SetPower(float _power);
	math::Vector4 m_color;

	template<class T>
	std::weak_ptr<T> AddShadowMapComponent() {
		static_assert(std::is_base_of<component::BaseCameraComponent, T>::value, "シャドウマップカメラを設定してください");

		// シャドウマップカメラコンポーネントを生成
		// 今後、AddComponentではシャドウマップカメラを
		// アタッチできないようにしなければいけない
		auto shadowMap = m_transform.lock()->m_gameObject->AddComponent<T>();
		return shadowMap;
	}
protected:
	void SetMyLightType(LIGHT_TYPE _lightType);

private:
	LIGHT_TYPE m_myType;
};

}
}