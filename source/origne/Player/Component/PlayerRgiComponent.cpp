#include "PlayerRgiComponent.h"
#include "./core/Input/Input.h"

namespace mslib {
namespace origin {
namespace game {
PlayerRpgComponent::PlayerRpgComponent(std::array<int, static_cast<int>(STATUS::MAX)>* _status):
	m_status(_status){}

void PlayerRpgComponent::Initialize() {
	for (auto&itr : m_buffStatus) itr = 0;
	m_playerBattleCommand = static_cast<int>(PlayerBattleCommand::ATTACK);
}

void PlayerRpgComponent::Update() {
	switch (m_state) {
		// エンカウント中
	case PlayerState::ENCOUNTER:
		EncountUpdate();
		// if (fadeinFlag == true) {
		// 	m_state = PlayerState::COMMAND_CHOICE;
		// }
		break;

		// コマンド選択
	case PlayerState::COMMAND_CHOICE:
		BattleCommandUpdate();
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
		// フィールドのアップデート
	case PlayerState::FIELD:

		break;
	}

}

void PlayerRpgComponent::SetEncountState(PlayerState _state) {
	if (_state == PlayerState::ENCOUNTER || _state == PlayerState::ENCOUNTER_ENEMY_ATTACK || _state == PlayerState::ENCOUNTER_ATTACK) {
		m_state = _state;
		return;
	}
	m_state = PlayerState::ENCOUNTER;
}

// コマンド選択するステート
void PlayerRpgComponent::BattleCommandUpdate() {
	if (input::Input::GetKeyEnter(DIK_UPARROW)) {
		m_playerBattleCommand = m_playerBattleCommand--;
		if (m_playerBattleCommand == -1) {
			m_playerBattleCommand = static_cast<int>(PlayerBattleCommand::MAX) - 1;
		}
	}

	if (input::Input::GetKeyEnter(DIK_DOWNARROW)) {
		m_playerBattleCommand = m_playerBattleCommand++; 
		if (m_playerBattleCommand == static_cast<int>(PlayerBattleCommand::MAX)) {
			m_playerBattleCommand = 0;
		}
	}

	// 選択のキー入力がないのであれば返す
	if (!input::Input::GetKeyEnter(MSK_SPACE))return;

	switch (static_cast<PlayerBattleCommand>(m_playerBattleCommand)) {
	case PlayerBattleCommand::ATTACK:
		m_state = PlayerState::ATTACK_CHOICE;
		break;

	case PlayerBattleCommand::DEFENSE:
		// 防御力アップする
		m_buffStatus[static_cast<int>(STATUS::DEFENSE)] += 3;
		break;

	case PlayerBattleCommand::SKILL:
		break;

	case PlayerBattleCommand::ESCAPE:
		break;

	case PlayerBattleCommand::BACK:
		// いらない？
		break;
	}
}

void PlayerRpgComponent::AttackUpdate() {
}

void PlayerRpgComponent::EnemyAttackUpdate() {
}

void PlayerRpgComponent::EncountUpdate() {
	m_state = PlayerState::COMMAND_CHOICE;
}

}
}
}

