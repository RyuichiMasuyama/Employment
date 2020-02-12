#include "LoadEnemyGameObject.h"
#include "EnemyLoad.h"

namespace mslib {
namespace origin {
namespace game {

LoadEnemyGameObject::LoadEnemyGameObject(unsigned int _enemyNumber) :m_enemyNumber(_enemyNumber){
}

void LoadEnemyGameObject::Initialize() {
	loader::EnemyLoader::GetInstance().Load(m_enemyNumber);

}

}
}
}