#include "PlayerRgiComponent.h"

namespace mslib {
namespace origin {
namespace game {

void PlayerRpgComponent::Initialize() {

}

void PlayerRpgComponent::Update() {
	switch (m_state) {
		// �G���J�E���g��
	case PlayerState::ENCOUNTER:
		if (fadeinFlag == true) {
			m_state = PlayerState::COMMAND_CHOICE;
		}
		break;

		// �R�}���h�I��
	case PlayerState::COMMAND_CHOICE:

		break;
		// �U���R�}���h�I��
	case PlayerState::ATTACK_CHOICE:

		break;
		
		// �U��
	case PlayerState::ATTACK:
		AttackUpdate();
		break;

		// �G�U��
	case PlayerState::ENEMY:

		break;
	}

}

void PlayerRpgComponent::BattleCommandUpdate() {
}

void PlayerRpgComponent::AttackUpdate() {
	switch (m_playerBattleCommand) {
	case PlayerBattleCommand::ATTACK:
		break;
	case PlayerBattleCommand::DEFENSE:
		break;
	case PlayerBattleCommand::SKILL:
		break;
	case PlayerBattleCommand::ESCAPE:
		break;
	case PlayerBattleCommand::BACK:
		break;
	}
}

void PlayerRpgComponent::EnemyAttackUpdate() {
}

}
}
}

