#include "./PlayerGameObject.h"

#include "./core/Component/Render/RenderComponent.h"

namespace mslib {
namespace origin {
namespace game {

void PlayerGameObject::Initialize() {
	mesh::MeshLoader loader;
	AddComponent<component::RenderComponent>(loader.Load("assets/charModel.msobj"));

	CreateUpdateFunction(RpgUpdateName, &PlayerGameObject::RpgUpdate, this);
	CreateUpdateFunction(FieldUpdateName, &PlayerGameObject::FieldUpdate, this);

	// とりあえずアップデートをPRGからスタートするようにする
	SetUpdateFunction(RpgUpdateName);
}

void PlayerGameObject::RpgUpdate() {

}

void PlayerGameObject::FieldUpdate() {

}

}  // namespace game
}  // namespace origne
}  // namespace mslib
