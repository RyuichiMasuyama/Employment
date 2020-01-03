#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace object {
class FieldGameObject :public GameObject{
	BASE_CLASS_IS(GameObject)
public:
	FieldGameObject() = default;
	~FieldGameObject() = default;

	void Initialize()override;
};
}
}