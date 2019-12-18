#include "./RpgManagerComponent.h"
#include "../GameObject/RpgManagerGameObject.h"

namespace mslib {
namespace origin {
namespace manager {

RpgManagerComponent::RpgManagerComponent(int _battlePhase) {
	m_battlePhase = static_cast<int>(BATTLE_PHASE::Player);
}

void RpgManagerComponent::Initialize() {
	base::Initialize();
}

void RpgManagerComponent::Update() {

}

}
}
}