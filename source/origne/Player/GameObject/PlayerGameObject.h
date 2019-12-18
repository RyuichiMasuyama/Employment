#pragma once

#include <array>
#include "./core/Object/object.h"

namespace mslib {
namespace origin {
namespace game {

enum class STATUS {
	ATTACK,
	DEFENSE,
	SPEED,
	MAX,
};

class PlayerRpgComponent;
using PlayerRpgComponentPtr = std::weak_ptr<PlayerRpgComponent>;

class PlayerGameObject :public object::GameObject {
	BASE_CLASS_IS(object::GameObject)

public:
	static constexpr const char* PlayerGameObjectName = "PlayerGameObject";

	static constexpr const char* RpgUpdateName = "RpgUpdate";
	static constexpr const char* FieldUpdateName = "FieldUpdate";

private:
	// Rpg�퓬���̃A�b�v�f�[�g
	void RpgUpdate();
	// field�ŃG���J�E���g�܂ł̃A�b�v�f�[�g
	void FieldUpdate();

	// �e��X�e�[�^�X
	std::array<int, static_cast<int>(STATUS::MAX) > m_status;

	PlayerRpgComponentPtr m_playerRpgComponetPtr;
public:
	void Initialize() override;
};

}  // namespace game
}  // namespace origne
}  // namespace mslib