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
	Player,	// プレイヤーのフェイズ
	Enemy,	// エネミーのフェイズ
	Event,	// 何かのイベントのフェイズ一応記入
	MAX		// MAX
};

// RPGシーン全体を管理するオブジェクト
// 敵をスポーンさせてからSceneアウトまでを行う
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
