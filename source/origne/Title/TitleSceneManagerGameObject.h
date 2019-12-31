#pragma once

#include "./core/Object/object.h"

#include "../../core/Input/Input.h"

namespace mslib {
namespace object {

// �O���錾
class TitleSceneManagerGameObject;
using TitleSceneManagerGameObjectPtr = std::weak_ptr<TitleSceneManagerGameObject>;
using TitleSceneManagerGameObjectSPtr = std::shared_ptr<TitleSceneManagerGameObject>;



class TitleSceneManagerGameObject :public object::GameObject{
	BASE_CLASS_IS(object::GameObject)
	static constexpr const char* OBJECT_NAME = "TitleSceneManagerGameObject";
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	TitleSceneManagerGameObject() = default;
	~TitleSceneManagerGameObject() = default;

	// ������
	void Initialize()override {
		base::Initialize();

		// ������
		m_pushAnyKey = false;
	};

	// �σA�b�v�f�[�g
	void Update() override{

		if (input::Input::GetAnyEnter()) {
			m_pushAnyKey = true;
		}
	}

private:
	// �L�[�������ꂽ��true��
	bool m_pushAnyKey;
};
}
}