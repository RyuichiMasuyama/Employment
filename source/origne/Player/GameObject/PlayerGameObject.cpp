#include "./PlayerGameObject.h"
#include "./AssetManager/ModelLoader.h"
#include "../Component/PlayerRgiComponent.h"
#include "./core/Component/Render/ModelRenderComponent.h"

namespace mslib {
namespace origin {
namespace game {

void PlayerGameObject::Initialize() {
	base::Initialize();
	m_modelData.Load("assets/charModel.fbx");
	AddComponent<component::ModelRenderComponent>(&m_modelData);

	CreateUpdateFunction(RpgUpdateName, &PlayerGameObject::RpgUpdate, this);
	CreateUpdateFunction(FieldUpdateName, &PlayerGameObject::FieldUpdate, this);

	// とりあえずアップデートをFieldからする
	SetUpdateFunction(FieldUpdateName);

	// statusをすべて1で設定
	for (auto&itr : m_status) {
		itr = 1;
	}

	m_playerRpgComponetPtr = AddComponent<PlayerRpgComponent>(&m_status);

	// とりあえず普通にエンカウント
	m_playerRpgComponetPtr.lock()->SetEncountState(PlayerState::FIELD);
}

void PlayerGameObject::RpgUpdate() {

}

void PlayerGameObject::FieldUpdate() {
	if (false) {
		// とりあえず普通にエンカウント
		m_playerRpgComponetPtr.lock()->SetEncountState(PlayerState::ENCOUNTER);
	}
	
}

}  // namespace game
}  // namespace origne
}  // namespace mslib
