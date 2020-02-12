#pragma once
#include <core/Object/object.h>

namespace mslib {
namespace origin {
namespace game {
class EnemyGameObject;
using EnemyGameObjectSPtr = std::shared_ptr<EnemyGameObject>;
}
}
namespace object {

class EnemyManagerGameObject;
using EnemyManagerGameObjectPtr = std::weak_ptr<EnemyManagerGameObject>;
using EnemyManagerGameObjectSPtr = std::shared_ptr<EnemyManagerGameObject>;

class EnemyManagerGameObject :public GameObject {
	BASE_CLASS_IS(GameObject)
	static constexpr const char* ClassName = "EnemyManagerGameObject";
public:
	EnemyManagerGameObject() = default;
	~EnemyManagerGameObject() = default;

	void Initialize()override;

	// ÉXÉ|Å[ÉìÇ≥ÇπÇÈ
	void Spawn();
private:
	std::vector<origin::game::EnemyGameObjectSPtr> m_objectDinamicArray;
};
}
}