#pragma once

#include <array>
#include "./core/Object/object.h"
#include "./Renderer/Model.h"
#include <origne/Camera/HaveCameraGameObject.h>
#include <./origne/Status.h>
#include "./PlayerCommandModelGameObject.h"

namespace mslib {
namespace origin {
namespace game {
struct PlayerStatus:public object::Status {

};
class PlayerRpgComponent;
using PlayerRpgComponentPtr = std::weak_ptr<PlayerRpgComponent>;
using PlayerRpgComponentSPtr = std::shared_ptr<PlayerRpgComponent>;

class PlayerGameObject;
using PlayerGameObjectPtr = std::weak_ptr<PlayerGameObject>;
using PlayerGameObjectSPtr = std::shared_ptr<PlayerGameObject>;

class PlayerGameObject :public object::GameObject {
	BASE_CLASS_IS(object::GameObject)

public:
	static constexpr const char* PlayerGameObjectName = "PlayerGameObject";

	static constexpr const char* RpgUpdateName = "RpgUpdate";
	static constexpr const char* FieldUpdateName = "FieldUpdate";

	PlayerGameObject(mslib::object::HaveCameraGameObjectSPtr _cameraObejctPtr);
	// PlayerGameObject() = default;
	~PlayerGameObject() = default;
private:
	// Rpg戦闘時のアップデート
	void RpgUpdate();
	// fieldでエンカウントまでのアップデート
	void FieldUpdate();

	// 各種ステータス
	PlayerStatus m_status;

	// プレイヤーのコンポーネント
	PlayerRpgComponentPtr m_playerRpgComponetPtr;
	object::HaveCameraGameObjectSPtr m_cameraObejctPtr;
	// モデルデータ
	render::ModelData m_modelData;
	float m_moveSpd;
	math::Vector3 m_cameraPos;
	float m_rotLength;
	math::Vector2 m_rot;

	bool m_encount;

	std::vector<PlayerCommandModelGameObjectSPtr> m_playerCommandModelGameObjectDynamicArrayPtr;
public:
	void Initialize() override;
	void ImGuiDraw() override;

	void Encount();
	
};

}  // namespace game
}  // namespace origne
}  // namespace mslib