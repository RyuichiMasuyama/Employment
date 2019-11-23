#pragma once
#ifndef GAME_OBEJCT_MANAGER_H_
#define GAME_OBEJCT_MANAGER_H_

#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include "./core/Object/Object.h"
#include "./Singleton.h"

// ゲームオブジェクトの生成
// これを通すか、GameoObjectManagerを通します
#define CREATE_GAME_OBJECT(CreateClass, ...) mslib::manager::GameObjectManager::GetInstance().CreateGameObject<CreateClass>(__VA_ARGS__);

namespace mslib {
namespace object {
class GameObject;
using GameObjectSPtr = std::shared_ptr<GameObject>;
}

namespace manager {

// Singleton使用
// ゲームオブジェクトの管理
class GameObjectManager :public pattern::Singleton<GameObjectManager> {

public:
	template<class T, class... LIST>
	std::shared_ptr<T> CreateGameObject(LIST&&... _list) {
		static_assert(std::is_base_of<object::GameObject, T>::value,"ゲームオブジェクトを継承してください");
		auto result = std::make_shared<T>(_list...);

		result->Initialize();

		m_gameObjectList.push_back(result);

		return result;
	}

	void Update();
	void FixedUpdate() { for (auto itr : m_gameObjectList) { itr->FixedUpdate(); } }

	void ShowImGui();

private:
	std::vector<object::GameObjectSPtr> m_gameObjectList;

};

}
}

#endif  // GAME_OBEJCT_MANAGER_H_