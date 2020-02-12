#pragma once

#include "./core/Object/object.h"
#include "./Renderer/Model.h"
#include <./origne/Status.h>

namespace mslib {
namespace origin {
namespace game {

class PlayerCommandModelGameObject;
using PlayerCommandModelGameObjectPtr = std::weak_ptr<PlayerCommandModelGameObject>;
using PlayerCommandModelGameObjectSPtr = std::shared_ptr<PlayerCommandModelGameObject>;

class PlayerCommandModelGameObject :public object::GameObject {
	BASE_CLASS_IS(object::GameObject)

public:
	static constexpr const char* PlayerGameObjectName = "PlayerCommandModelGameObject";

	PlayerCommandModelGameObject(std::string _textureName);
	~PlayerCommandModelGameObject() = default;
private:
	std::string m_texutreName;
	render::ModelData m_modelData;
public:
	void Initialize() override;
	// void ImGuiDraw() override;
};

}  // namespace game
}  // namespace origne
}  // namespace mslib