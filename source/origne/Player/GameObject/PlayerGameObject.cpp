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

	// �Ƃ肠�����A�b�v�f�[�g��PRG����X�^�[�g����悤�ɂ���
	SetUpdateFunction(RpgUpdateName);

	// status�����ׂ�1�Őݒ�
	for (auto&itr : m_status) {
		itr = 1;
	}

	m_playerRpgComponetPtr = AddComponent<PlayerRpgComponent>(&m_status);

	// �Ƃ肠�������ʂɃG���J�E���g
	m_playerRpgComponetPtr.lock()->SetEncountState(PlayerState::ENCOUNTER);
}

void PlayerGameObject::RpgUpdate() {

}

void PlayerGameObject::FieldUpdate() {
	// �Ƃ肠�������ʂɃG���J�E���g
	m_playerRpgComponetPtr.lock()->SetEncountState(PlayerState::ENCOUNTER);
}

}  // namespace game
}  // namespace origne
}  // namespace mslib
