#pragma once

#include "./core/Object/object.h"
#include <Renderer/Model.h>

namespace mslib {
namespace object {

class FieldGameObject;
using FieldGameObjectPtr = std::weak_ptr<FieldGameObject>;
using FieldGameObjectSPtr = std::shared_ptr<FieldGameObject>;

class FieldGameObject :public GameObject{
	BASE_CLASS_IS(GameObject)
public:
	FieldGameObject() = default;
	~FieldGameObject() = default;

	void Initialize()override;
private:
	render::ModelData m_modelData;
};
}
}