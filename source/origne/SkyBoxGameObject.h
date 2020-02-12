#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace object {
class SkyBoxGameObject :public GameObject {
	BASE_CLASS_IS(GameObject)
private:

public:
	SkyBoxGameObject() = default;
	~SkyBoxGameObject() = default;

	void Initialize() override;
};
}
}