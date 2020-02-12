#pragma once

#include "./core/Object/object.h"
#include "./EnemyGameObject.h"

namespace mslib {
namespace origin {
namespace game {

class LoadEnemyGameObject;
using LoadEnemyGameObjectPtr = std::weak_ptr<LoadEnemyGameObject>;

class LoadEnemyGameObject :public EnemyGameObject {
	BASE_CLASS_IS(EnemyGameObject)
		static constexpr const char* PlayerGameObjectName = "LoadEnemyGameObject";
public:
	LoadEnemyGameObject(unsigned int _enemyNumber);
	~LoadEnemyGameObject() = default;
private:
	void RpgUpdate();

	// エネミーナンバーを設定
	// スポーンしてからは変更されない
	const unsigned int m_enemyNumber;
public:
	void Initialize() override;
};

}  // namespace game
}  // namespace origne
}  // namespace mslib
