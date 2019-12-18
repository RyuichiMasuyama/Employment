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
	ENCOUNTER,		// �������̃A�b�v�f�[�g(���Ԃ�Fi�V�[���J�ڂ��I���܂�)
	ENCOUNTER_ATTACK,// �������ɍU���������������̃A�b�v�f�[�g
	ENCOUNTER,		// �������ɓG�U���������������̃A�b�v�f�[�g
	COMMAND_CHOICE,	// �R�}���h�I���̃X�e�[�g
	ATTACK_CHOICE,	// �A�^�b�N�I���̃X�e�[�g
	ATTACK,			// �A�^�b�N���̃X�e�[�g
	ENEMY,			// �G�l�~�[�̃^�[�����̃X�e�[�g
	MAX,			// MAX
};

// �v���C���[��RPG�G���J�E���g���̃R���|�[�l���g
class PlayerRpgComponent :public component::Component {
	BASE_CLASS_IS(Component)
public:
	void Initialize() override;
	void Update()override;

private:
	// �o�g���R�}���h�I���������̃A�b�v�f�[�g
	void BattleCommandUpdate();

	// �A�^�b�N���̃A�b�v�f�[�g
	void AttackUpdate();

	// �G�l�~�[�̍U�����̃A�b�v�f�[�g(���Ԃ񂱂��Ŗh��Ƃ�������Ǝv��)
	void EnemyAttackUpdate();



	// �v���C���[�X�e�[�g
	PlayerState m_state;

	// �I�𒆃R�}���h
	PlayerBattleCommand m_playerBattleCommand;
};

}  // namespace game
}  // namespace orign
}  // namespace mslib