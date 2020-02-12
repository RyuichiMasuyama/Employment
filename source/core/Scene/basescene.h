#pragma once

#include "./core/base.h"
#include "../Object/Object.h"
#include "./origne/Camera/HaveCameraGameObject.h"
#include <./GameObjectManager.h>

#include <vector>

namespace mslib {
namespace scene {

// �V�[���͂��ׂĂ�����p������
class BaseScene :public mslib::core::base {

private:
	std::vector<object::ObjectSPtr> m_object;

public:
	// �K�{�֐�
	virtual void Update() = 0;

	// �C�ӊ֐�
	// ���[�h
	virtual void ImGuiDraw() {};	// ���ݎg�p�\��͂Ȃ�
	virtual void Draw() {};			// ���ݎg�p�\��͂Ȃ�
	virtual void Load() {};
	virtual void UnLoad() {};

	virtual void UnActive() {};		// �V�����V�[����ǂݍ��݁A���̃V�[����stack���ꂽ�Ƃ�
	virtual void OnActive() {};		// ��̃V�[����UnLoad���ꂽ�Ƃ�
protected:
	void AllObjectUpdate();		// �S�̂̃A�b�v�f�[�g
	void AllImGuiDraw();		// �S�̂�ImGui�̕`��
	void IncetanceObject(object::ObjectSPtr _object); // ���������I�u�W�F�N�g������

	// object::HaveCameraGameObjectSPtr m_haveCamera;
};

}
}