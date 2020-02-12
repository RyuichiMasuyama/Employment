#include "EnemyManagerGameObject.h"
#include "./LoadEnemyGameObject.h"
#include <./GameObjectManager.h>

namespace mslib {
namespace object {
void EnemyManagerGameObject::Initialize() {
	base::Initialize();
	SetClassName("EnemyManagerGameObject");
}
void EnemyManagerGameObject::Spawn() {
	auto spawnObj = CREATE_GAME_OBJECT(origin::game::LoadEnemyGameObject, 0);
	m_objectDinamicArray.push_back(spawnObj);
}
}
}