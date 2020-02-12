#pragma once

#include <core/Object/object.h>
#include "./origne/Player/GameObject/PlayerGameObject.h"
#include <origne/Camera/HaveCameraGameObject.h>

#include <ImGui/imgui.h>

namespace mslib {
namespace manager {

class FieldManagerGameObject;
using FieldManagerGameObjectPtr = std::weak_ptr<FieldManagerGameObject>;
using FieldManagerGameObjectSPtr = std::shared_ptr<FieldManagerGameObject>;

class FieldManagerGameObject:public object::GameObject  {
	BASE_CLASS_IS(object::GameObject)

	static constexpr const char* ObjectName= "FieldManager";
	static constexpr const char* FieldUpdateName = "FieldUpdate";
public:
	FieldManagerGameObject(origin::game::PlayerGameObjectPtr _playerGameObjectPtr,object::HaveCameraGameObjectPtr _haveCameraGameObjectPtr);
	~FieldManagerGameObject() = default;

	void Initialize()override;

	void ImGuiDraw()override;

	void AfterUpdate()override;
private:
	void FieldUpdate();

	origin::game::PlayerGameObjectPtr m_playerGameObjectPtr;
	object::HaveCameraGameObjectPtr m_haveCameraGameObjectPtr;

	bool m_enemyEnter;
	float m_feadLevel;
	bool m_feadIn;
	bool m_feadOut;
	bool m_sceneChange;
};

}
}