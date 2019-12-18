#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace origin {
namespace game {

enum class PlayerBattleCommand {
	ATTACK,
	DEFENSE,
	SKILL,
	ESCAPE,
	BACK,
	MAX,
};

enum class PlayerState {
	ENCOUNTER,		// 遭遇時のアップデート(たぶんFiシーン遷移が終わるまで)
	ENCOUNTER_ATTACK,// 遭遇時に攻撃が発生した時のアップデート
	ENCOUNTER,		// 遭遇時に敵攻撃が発生した時のアップデート
	COMMAND_CHOICE,	// コマンド選択のステート
	ATTACK_CHOICE,	// アタック選択のステート
	ATTACK,			// アタック時のステート
	ENEMY,			// エネミーのターン時のステート
	MAX,			// MAX
};

// プレイヤーのRPGエンカウント時のコンポーネント
class PlayerRpgComponent :public component::Component {
	BASE_CLASS_IS(Component)
public:
	void Initialize() override;
	void Update()override;

private:
	// バトルコマンド選択した時のアップデート
	void BattleCommandUpdate();

	// アタック中のアップデート
	void AttackUpdate();

	// エネミーの攻撃中のアップデート(たぶんここで防御とかを入れると思う)
	void EnemyAttackUpdate();



	// プレイヤーステート
	PlayerState m_state;

	// 選択中コマンド
	PlayerBattleCommand m_playerBattleCommand;
};

}  // namespace game
}  // namespace orign
}  // namespace mslib