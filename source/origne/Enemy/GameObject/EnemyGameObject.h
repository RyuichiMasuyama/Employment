#pragma once

#include "./core/Object/object.h"
#include <./origne/Status.h>

namespace mslib {
namespace origin {
namespace game {
struct EnemyStatus :public object::Status {
	std::string m_modelFilePaht;
};
class EnemyGameObject;
using EnemyGameObjectPtr = std::weak_ptr<EnemyGameObject>;


// RPG�V�[���S�̂��Ǘ�����I�u�W�F�N�g
// �G���X�|�[�������Ă���Scene�A�E�g�܂ł��s��
class EnemyGameObject :public object::GameObject {
	BASE_CLASS_IS(object::GameObject)
	static constexpr const char* PlayerGameObjectName = "EnemyGameObject";
public:
	EnemyGameObject();
	~EnemyGameObject() = default;
private:
	void RpgUpdate();
	void FieldUpdate();
public:
	void Initialize() override;
	EnemyStatus m_status;
};

}  // namespace game
}  // namespace origne
}  // namespace mslib
