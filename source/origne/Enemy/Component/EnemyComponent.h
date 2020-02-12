#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace origin {
namespace game {

class EnemyComponent;
using EnemyComponentPtr = std::weak_ptr<EnemyComponent>;

// RPGシーン全体を管理するオブジェクト
// 敵をスポーンさせてからSceneアウトまでを行う
class EnemyComponent:public component::Component {
	BASE_CLASS_IS(component::Component)
	static constexpr const char* PlayerGameObjectName = "EnemyComponent";
public:
	void Initialize() override;
	void Update() override;
private:
	void FieldUpdate();
	void RpgUpdate();
};

}  // namespace game
}  // namespace origne
}  // namespace mslib
