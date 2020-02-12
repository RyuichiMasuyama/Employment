#include "BaseScene.h"
#include <algorithm>

namespace mslib {
namespace scene {

// �S���̃I�u�W�F�N�g�̃A�b�v�f�[�g�D��x�ȂǍ��͖���
// �I�u�W�F�N�g�̒��g�������Ă�����j��������
void BaseScene::AllObjectUpdate() {
	// CreanUp
	std::vector<object::ObjectPtr> result;
	for (auto itr : m_object) {
		result.push_back(itr);
	}

	// Update
	for (auto itr : m_object) {
		itr->Update();
	}
}

void BaseScene::AllImGuiDraw() {
	// ImGui�̕`��
	for (auto itr : m_object) {
		itr->ImGuiDraw();
	}
}

// �I�u�W�F�N�g�̒ǉ��E���[�h�֐����Ŏg���\��
void BaseScene::IncetanceObject(object::ObjectSPtr _object) {
	m_object.push_back(_object);
}

}
}