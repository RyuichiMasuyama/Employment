#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace origin {
namespace game {

class RpgManagerComponent;
using RpgManagerComponentPtr = std::weak_ptr<RpgManagerComponent>;

// RPG�V�[���S�̂��Ǘ�����I�u�W�F�N�g
// �G���X�|�[�������Ă���Scene�A�E�g�܂ł��s��
class EnemyGameObject :public object::GameObject {
	BASE_CLASS_IS(object::GameObject)
		static constexpr const char* PlayerGameObjectName = "EnemyGameObject";
private:
	void RpgUpdate();
	void BeforUpdate() override;

public:
	void Initialize() override;

};

}  // namespace game
}  // namespace origne
}  // namespace mslib
