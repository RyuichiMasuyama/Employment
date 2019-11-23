#include "GameObjectManager.h"

namespace mslib {
namespace manager {

void GameObjectManager::Update() {
	for (auto itr : m_gameObjectList) {
		itr->Update();
	}

	// 参照カウンタが1の場合消去する
	auto result = std::remove_if(m_gameObjectList.begin(), m_gameObjectList.end(),
		[](auto itr) { return itr.use_count() == 1; });

	m_gameObjectList.erase(result, m_gameObjectList.end());
}

void GameObjectManager::ShowImGui() {
#ifndef _DEBUG
#else
	for (auto itr : m_gameObjectList) {

		itr->ImGuiDraw();
	}
#endif // !_DEBUG

}

}
}