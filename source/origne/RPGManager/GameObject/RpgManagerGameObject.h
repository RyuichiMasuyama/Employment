#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace origin {
namespace manager {

class RpgManagerComponent;
using RpgManagerComponentPtr = std::weak_ptr<RpgManagerComponent>;

enum class BATTLE_PHASE{
	Player,	// プレイヤーのフェイズ
	Enemy,	// エネミーのフェイズ
	Event,	// 何かのイベントのフェイズ一応記入
	MAX		// MAX
};

// RPGシーン全体を管理するオブジェクト
// 敵をスポーンさせてからSceneアウトまでを行う
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
