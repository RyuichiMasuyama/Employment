#pragma once

#include "./core/Object/object.h"
#include "../GameObject/PlayerGameObject.h"

namespace mslib {
namespace origin {
namespace game {

enum class PlayerBattleCommand {
	ATTACK,			// アタック
	DEFENSE,		// ディフェンス
	SKILL,			// スキル
	ESCAPE,			// 逃げる
	BACK,			// ステート選択に戻る
	MAX,
};

enum class PlayerState {
	FIELD,			// フィールドのアップデート
	ENCOUNTER,		// 遭遇時のアップデート(たぶんFiシーン遷移が終わるまで)
	ENCOUNTER_ATTACK,// 遭遇時に攻撃が発生した時のアップデート
	ENCOUNTER_ENEMY_ATTACK,		// 遭遇時に敵攻撃が発生した時のアップデート
	COMMAND_CHOICE,	// コマンド選択のステート
	ATTACK_CHOICE,	// アタック選択のステート
	SKILL_CHOICE,	// スキル選択のステーと
	ATTACK,			// アタック時のステート
	ENEMY,			// エネミーのターン時のステート
	MAX,			// MAX
};

// プレイヤーのRPGエンカウント時のコンポーネント
class PlayerRpgComponent :public component::Component {
	BASE_CLASS_IS(Component)
public:
	PlayerRpgComponent(std::array<int, static_cast<int>(STATUS::MAX)>* _status);
	~PlayerRpgComponent() = default;

	void Initialize() override;
	void Update() override;

	// エンカウントする時にセットするプレイヤーのステート
	// エンカウント以外のステートが入ると普通のエンカウントになる
	void SetEncountState(PlayerState _state);
private:
	// バトルコマンド選択した時のアップデート
	void BattleCommandUpdate();

	// アタックコマンドを選択する
	void AttackCommandUpdate();

	// アタック中のアップデート
	void AttackUpdate();

	// エネミーの攻撃中のアップデート(たぶんここで防御とかを入れると思う)
	void EnemyAttackUpdate();

	// 通常のエンカウントのUpdate
	void EncountUpdate();

	// プレイヤーステート
	PlayerState m_state;

	// 選択中コマンド(PlayerBattleCommand)
	// インクリメントを多用する可能性があるのでint型で宣言
	int m_playerBattleCommand;

	// 選択したかのフラグ
	bool m_playerBattleCommandFlag;

	// ゲームオブジェクトのステータスを受け取るポインタ
	std::array<int, static_cast<int>(STATUS::MAX) > *m_status;

	// ゲームオブジェクトのステータスに干渉しない用のバフステータス
	std::array<int, static_cast<int>(STATUS::MAX) > m_buffStatus;
};

}  // namespace game
}  // namespace orign
}  // namespace mslib