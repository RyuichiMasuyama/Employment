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


// RPGシーン全体を管理するオブジェクト
// 敵をスポーンさせてからSceneアウトまでを行う
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
