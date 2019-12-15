#include "GameObjectManager.h"

namespace mslib {
namespace manager {

void GameObjectManager::Update() {
	for (auto itr : m_gameObjectList) {
		itr->Update();
	}

	// �Q�ƃJ�E���^��1�̏ꍇ��������
	auto result = std::remove_if(m_gameObjectList.begin(), m_gameObjectList.end(),
		[](auto itr) { return itr.use_count() == 1; });

	m_gameObjectList.erase(result, m_gameObjectList.end());
}

void GameObjectManager::FixedUpdate() {
	for (auto itr : m_gameObjectList) { itr->FixedUpdate(); }
	TransformUpdate();
}

void GameObjectManager::ShowImGui() {
#ifndef _DEBUG
#else
	for (auto itr : m_gameObjectList) {

		itr->ImGuiDraw();
	}
#endif // !_DEBUG

}

void GameObjectManager::TransformUpdate() {
	for (auto itr : m_gameObjectList) {
		// ��ԏ�̐e�̂ݍX�V
		itr->TransformUpdate();
	}
}


}
}