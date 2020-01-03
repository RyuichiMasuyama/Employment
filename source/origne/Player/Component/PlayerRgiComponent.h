#pragma once

#include "./core/Object/object.h"
#include "../GameObject/PlayerGameObject.h"

namespace mslib {
namespace origin {
namespace game {

enum class PlayerBattleCommand {
	ATTACK,			// �A�^�b�N
	DEFENSE,		// �f�B�t�F���X
	SKILL,			// �X�L��
	ESCAPE,			// ������
	BACK,			// �X�e�[�g�I���ɖ߂�
	MAX,
};

enum class PlayerState {
	FIELD,			// �t�B�[���h�̃A�b�v�f�[�g
	ENCOUNTER,		// �������̃A�b�v�f�[�g(���Ԃ�Fi�V�[���J�ڂ��I���܂�)
	ENCOUNTER_ATTACK,// �������ɍU���������������̃A�b�v�f�[�g
	ENCOUNTER_ENEMY_ATTACK,		// �������ɓG�U���������������̃A�b�v�f�[�g
	COMMAND_CHOICE,	// �R�}���h�I���̃X�e�[�g
	ATTACK_CHOICE,	// �A�^�b�N�I���̃X�e�[�g
	SKILL_CHOICE,	// �X�L���I���̃X�e�[��
	ATTACK,			// �A�^�b�N���̃X�e�[�g
	ENEMY,			// �G�l�~�[�̃^�[�����̃X�e�[�g
	MAX,			// MAX
};

// �v���C���[��RPG�G���J�E���g���̃R���|�[�l���g
class PlayerRpgComponent :public component::Component {
	BASE_CLASS_IS(Component)
public:
	PlayerRpgComponent(std::array<int, static_cast<int>(STATUS::MAX)>* _status);
	~PlayerRpgComponent() = default;

	void Initialize() override;
	void Update() override;

	// �G���J�E���g���鎞�ɃZ�b�g����v���C���[�̃X�e�[�g
	// �G���J�E���g�ȊO�̃X�e�[�g������ƕ��ʂ̃G���J�E���g�ɂȂ�
	void SetEncountState(PlayerState _state);
private:
	// �o�g���R�}���h�I���������̃A�b�v�f�[�g
	void BattleCommandUpdate();

	// �A�^�b�N�R�}���h��I������
	void AttackCommandUpdate();

	// �A�^�b�N���̃A�b�v�f�[�g
	void AttackUpdate();

	// �G�l�~�[�̍U�����̃A�b�v�f�[�g(���Ԃ񂱂��Ŗh��Ƃ�������Ǝv��)
	void EnemyAttackUpdate();

	// �ʏ�̃G���J�E���g��Update
	void EncountUpdate();

	// �v���C���[�X�e�[�g
	PlayerState m_state;

	// �I�𒆃R�}���h(PlayerBattleCommand)
	// �C���N�������g�𑽗p����\��������̂�int�^�Ő錾
	int m_playerBattleCommand;

	// �I���������̃t���O
	bool m_playerBattleCommandFlag;

	// �Q�[���I�u�W�F�N�g�̃X�e�[�^�X���󂯎��|�C���^
	std::array<int, static_cast<int>(STATUS::MAX) > *m_status;

	// �Q�[���I�u�W�F�N�g�̃X�e�[�^�X�Ɋ����Ȃ��p�̃o�t�X�e�[�^�X
	std::array<int, static_cast<int>(STATUS::MAX) > m_buffStatus;
};

}  // namespace game
}  // namespace orign
}  // namespace mslib