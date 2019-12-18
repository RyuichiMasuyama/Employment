#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace origin {
namespace game {

class PlayerGameObject :public object::GameObject {
	BASE_CLASS_IS(object::GameObject)

public:
	static constexpr const char* PlayerGameObjectName = "PlayerGameObject";

	static constexpr const char* RpgUpdateName = "RpgUpdate";
	static constexpr const char* FieldUpdateName = "FieldUpdate";

private:
	void RpgUpdate();
	void FieldUpdate();

public:
	void Initialize() override;

	
};

}  // namespace game
}  // namespace origne
}  // namespace mslib