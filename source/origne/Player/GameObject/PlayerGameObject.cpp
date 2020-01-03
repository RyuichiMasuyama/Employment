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

	// �Ƃ肠�����A�b�v�f�[�g��Field���炷��
	SetUpdateFunction(FieldUpdateName);

	// status�����ׂ�1�Őݒ�
	for (auto&itr : m_status) {
		itr = 1;
	}

	m_playerRpgComponetPtr = AddComponent<PlayerRpgComponent>(&m_status);

	// �Ƃ肠�������ʂɃG���J�E���g
	m_playerRpgComponetPtr.lock()->SetEncountState(PlayerState::FIELD);
}

void PlayerGameObject::RpgUpdate() {

}

void PlayerGameObject::FieldUpdate() {
	if (false) {
		// �Ƃ肠�������ʂɃG���J�E���g
		m_playerRpgComponetPtr.lock()->SetEncountState(PlayerState::ENCOUNTER);
	}
	
}

}  // namespace game
}  // namespace origne
}  // namespace mslib
