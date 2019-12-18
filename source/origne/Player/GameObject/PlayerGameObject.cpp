#include "./PlayerGameObject.h"

#include "./core/Component/Render/RenderComponent.h"
#include "../Component/PlayerRgiComponent.h"

namespace mslib {
namespace origin {
namespace game {

void PlayerGameObject::Initialize() {
	base::Initialize();

	mesh::MeshLoader loader;
	AddComponent<component::RenderComponent>(loader.Load("assets/charModel.msobj"));

	CreateUpdateFunction(RpgUpdateName, &PlayerGameObject::RpgUpdate, this);
	CreateUpdateFunction(FieldUpdateName, &PlayerGameObject::FieldUpdate, this);

	// とりあえずアップデートをPRGからスタートするようにする
	SetUpdateFunction(RpgUpdateName);

	// statusをすべて1で設定
	for (auto&itr : m_status) {
		itr = 1;
	}

	m_playerRpgComponetPtr = AddComponent<PlayerRpgComponent>(&m_status);

	// とりあえず普通にエンカウント
	m_playerRpgComponetPtr.lock()->SetEncountState(PlayerState::ENCOUNTER);
}

void PlayerGameObject::RpgUpdate() {

}

void PlayerGameObject::FieldUpdate() {
	// とりあえず普通にエンカウント
	m_playerRpgComponetPtr.lock()->SetEncountState(PlayerState::ENCOUNTER);
}

}  // namespace game
}  // namespace origne
}  // namespace mslib
