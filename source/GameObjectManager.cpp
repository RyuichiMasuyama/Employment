#include "GameObjectManager.h"

namespace mslib {
namespace manager {

void GameObjectManager::Update() {

	// 参照カウンタが1の場合消去する
	auto result = std::remove_if(m_gameObjectList.begin(), m_gameObjectList.end(),
		[](auto itr) {
		bool ret=itr.use_count() == 0;
		return  ret;
	});
	m_gameObjectList.erase(result, m_gameObjectList.end());

	for (auto itr : m_gameObjectList) {
		itr->Update();
	}

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
		// 一番上の親のみ更新
		itr->TransformUpdate();
	}
}


}
}