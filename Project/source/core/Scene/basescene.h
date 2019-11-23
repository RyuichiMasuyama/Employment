#pragma once

#include "./core/base.h"
#include "../Object/Object.h"

#include <vector>

namespace mslib {
namespace scene {

// �V�[���͂��ׂĂ�����p������
class BaseScene :public mslib::core::base {

private:
	std::vector<object::ObjectPtr> m_object;

public:
	// �K�{�֐�
	virtual void Update() = 0;
	virtual void Draw() {};
	virtual void ImGuiDraw() = 0;

	// �C�ӊ֐�
	// ���f���Ȃǂ̃��[�h�Ɏg��
	virtual void Load() {};
	virtual void UnLoad() {};

protected:
	void AllObjectUpdate();		// �S�̂̃A�b�v�f�[�g
	void AllImGuiDraw();		// �S�̂�ImGui�̕`��
	void IncetanceObject(object::ObjectPtr _object); // ���������I�u�W�F�N�g������
};

}
}