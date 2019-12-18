#include "./RpgManagerGameObject.h"
#include "../Component/RpgManagerComponent.h"

namespace mslib {
namespace origin {
namespace manager {

void RpgManagerGameObject::Initialize() {
	base::Initialize();
	m_rpgManagerCompoent = AddComponent<RpgManagerComponent>(static_cast<int>(BATTLE_PHASE::Player));
}
void RpgManagerGameObject::RpgUpdate() {

}

void RpgManagerGameObject::BeforUpdate() {
	
}

}
}
}