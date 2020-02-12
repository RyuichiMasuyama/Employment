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
	// Rpg�퓬���̃A�b�v�f�[�g
	void RpgUpdate();
	// field�ŃG���J�E���g�܂ł̃A�b�v�f�[�g
	void FieldUpdate();

	// �e��X�e�[�^�X
	PlayerStatus m_status;

	// �v���C���[�̃R���|�[�l���g
	PlayerRpgComponentPtr m_playerRpgComponetPtr;
	object::HaveCameraGameObjectSPtr m_cameraObejctPtr;
	// ���f���f�[�^
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