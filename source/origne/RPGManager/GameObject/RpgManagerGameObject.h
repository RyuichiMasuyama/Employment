#pragma once

#include "./core/Object/object.h"
#include <./origne/Camera/HaveCameraGameObject.h>
#include "./origne/Player/GameObject/PlayerGameObject.h"
#include <./origne/Enemy/GameObject/EnemyManagerGameObject.h>

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
	
	static constexpr const char* RpgManagerGameObjectName = "RpgManagerGameObject";
	static constexpr const char* RpgUpdateName = "RpgUpdate";
public:
	RpgManagerGameObject(
		object::HaveCameraGameObjectSPtr _haveCameraGameObject,
		origin::game::PlayerGameObjectSPtr _playerGameObject,
		object::EnemyManagerGameObjectSPtr _enemyManagerGameObject);
	~RpgManagerGameObject() = default;

	void Initialize() override;
private:
	void RpgUpdate();
	void BeforUpdate() override;

	float m_feadLevel;

	RpgManagerComponentPtr m_rpgManagerCompoent;

	object::HaveCameraGameObjectSPtr m_haveCameraGameObject;

	origin::game::PlayerGameObjectSPtr m_playerGameObject;
	object::EnemyManagerGameObjectSPtr m_enemyManagerGameObject;

	math::Matrix m_playerFiledMatrix;
};

}  // namespace game
}  // namespace origne
}  // namespace mslib
