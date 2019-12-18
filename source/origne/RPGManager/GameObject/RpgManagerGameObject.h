#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace origin {
namespace manager {

class RpgManagerComponent;
using RpgManagerComponentPtr = std::weak_ptr<RpgManagerComponent>;

enum class BATTLE_PHASE{
	Player,	// �v���C���[�̃t�F�C�Y
	Enemy,	// �G�l�~�[�̃t�F�C�Y
	Event,	// �����̃C�x���g�̃t�F�C�Y�ꉞ�L��
	MAX		// MAX
};

// RPG�V�[���S�̂��Ǘ�����I�u�W�F�N�g
// �G���X�|�[�������Ă���Scene�A�E�g�܂ł��s��
class RpgManagerGameObject :public object::GameObject {
	BASE_CLASS_IS(object::GameObject)
		static constexpr const char* PlayerGameObjectName = "RpgManagerGameObject";
private:
	void RpgUpdate();
	void BeforUpdate() override;

	RpgManagerComponentPtr m_rpgManagerCompoent;
public:
	void Initialize() override;

};

}  // namespace game
}  // namespace origne
}  // namespace mslib
