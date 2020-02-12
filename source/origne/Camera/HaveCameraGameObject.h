#pragma once
#include "./core/Object/object.h"
#include <./core/Component/PostEffect/BasePostEffectComponent.h>

namespace mslib {
namespace component {
class FeadComponent;
using FeadComponentPtr = std::weak_ptr<FeadComponent>;
}
namespace object{
class HaveCameraGameObject;
using HaveCameraGameObjectPtr = std::weak_ptr< HaveCameraGameObject>;
using HaveCameraGameObjectSPtr = std::shared_ptr< HaveCameraGameObject>;

class HaveCameraGameObject :public object::GameObject {
	BASE_CLASS_IS(GameObject)
public:
	static constexpr const char* ClassName = "HaveCameraGameObject";
	static constexpr const char* TestUpdateName = "TestUpdate";

	void Initialize() override;

	void ImGuiDraw() override;

	void SetFeadLevel(float _feadLevel);
private:
	// �|�X�g�G�t�F�N�g
	std::weak_ptr<component::BasePostEffectComponent> m_postEffect;

	// �|�X�g�G�t�F�N�g�̕ϐ�
	float m_gauusePower;
	float m_bloomPower;
	bool m_gauuseFlag;
	bool m_bloomFlag;
	float m_feadLevel;

	// �t�F�[�h�A�E�gComponent
	component::FeadComponentPtr m_feadComponent;

	// �A�b�v�f�[�g
	void TestUpdate();
};
}
}
