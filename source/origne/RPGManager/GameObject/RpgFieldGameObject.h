#pragma once

#include "./core/Object/object.h"
#include <./core/Component/Render/ModelRenderComponent.h>
namespace mslib {
namespace object {

class RpgFieldGameObject;
using RpgFieldGameObjectPtr = std::weak_ptr<RpgFieldGameObject>;

// 
class RpgFieldGameObject :public object::GameObject {
	BASE_CLASS_IS(object::GameObject)

		static constexpr const char* PlayerGameObjectName = "RpgFieldGameObject";
public:
	RpgFieldGameObject() = default;
	~RpgFieldGameObject() = default;

	void Initialize() override;

	void ImGuiDraw()override;
private:
	render::ModelData m_modelData;
};
}  // namespace object
}  // namespace mslib
