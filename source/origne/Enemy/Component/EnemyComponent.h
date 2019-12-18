#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace origin {
namespace game {

class RpgManagerComponent;
using RpgManagerComponentPtr = std::weak_ptr<RpgManagerComponent>;

// RPGシーン全体を管理するオブジェクト
// 敵をスポーンさせてからSceneアウトまでを行う
class EnemyComponent:public component::Component {
	BASE_CLASS_IS(object::GameObject)
		static constexpr const char* PlayerGameObjectName = "EnemyComponent";
private:
	
	void RpgUpdate();

public:
	void Initialize() override;

};

}  // namespace game
}  // namespace origne
}  // namespace mslib
