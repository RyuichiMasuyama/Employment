#pragma once

#include "./core/Object/object.h"

#include "../../core/Input/Input.h"
namespace mslib {
namespace object {

// �O���錾
class TitleSceneManagerGameObject;
using TitleSceneManagerGameObjectPtr = std::weak_ptr<TitleSceneManagerGameObject>;
using TitleSceneManagerGameObjectSPtr = std::shared_ptr<TitleSceneManagerGameObject>;

class HaveCameraGameObject;
using HaveCameraGameObjectPtr = std::weak_ptr<HaveCameraGameObject>;

class TitleSceneManagerGameObject :public object::GameObject{
	BASE_CLASS_IS(object::GameObject)
	static constexpr const char* OBJECT_NAME = "TitleSceneManagerGameObject";
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	TitleSceneManagerGameObject(HaveCameraGameObjectPtr _haveCameraObjectPtr);
	~TitleSceneManagerGameObject() = default;

	// ������
	void Initialize()override;

	// �σA�b�v�f�[�g
	void Update() override;

private:
	// �L�[�������ꂽ��true��
	bool m_pushAnyKey;

	float m_feadLevel;

	// �J�����������Ă���Q�[���I�u�W�F�N�g�̃|�C���^
	HaveCameraGameObjectPtr m_haveCameraGameObjectPtr;
};
}
}