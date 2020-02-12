#include "FieldManagerComponent.h"
#include <./core/scene/SceneManager.h>
#include <./origne/scene/BattleScene.h>

namespace mslib {
namespace component {
FieldManagerComponent::FieldManagerComponent(bool& _enemyEnter) :m_enemyEnter(_enemyEnter) {

}

void FieldManagerComponent::Initialize() {
}

void FieldManagerComponent::FixedUpdate() {
	if (m_enemyEnter) {
	}
}

}
}
