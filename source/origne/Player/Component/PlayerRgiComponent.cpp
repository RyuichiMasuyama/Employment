#include "PlayerRgiComponent.h"

namespace mslib {
namespace origin {
namespace game {

void PlayerRpgComponent::Initialize() {

}

void PlayerRpgComponent::Update() {
	switch (m_state) {
		// エンカウント中
	case PlayerState::ENCOUNTER:
		if (fadeinFlag == true) {
			m_state = PlayerState::COMMAND_CHOICE;
		}
		break;

		// コマンド選択
	case PlayerState::COMMAND_CHOICE:

		break;
		// 攻撃コマンド選択
	case PlayerState::ATTACK_CHOICE:

		break;
		
		// 攻撃
	case PlayerState::ATTACK:
		AttackUpdate();
		break;

		// 敵攻撃
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

