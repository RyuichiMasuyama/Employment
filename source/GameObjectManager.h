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
#define DELETE_GAME_OBJECT(DeleteClass) mslib::manager::GameObjectManager::GetInstance().DeleteGameObject(DeleteClass);
#define FIND_GAME_OBJECT(ClassName) mslib::manager::GameObjectManager::GetInstance().FinedGameObject(ClassName);
#define TYPE_FIND_GAME_OBJECT(TemplateClass,ClassName) mslib::manager::GameObjectManager::GetInstance().FinedGameObject<TemplateClass>(ClassName);

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

	object::GameObjectSPtr FinedGameObject(std::string _className) {
		for (auto itr : m_gameObjectList) {
			if (itr->ClassName() == _className) {
				return itr;
			}
		}
		return nullptr;
	}
	
	template<class T>
	std::shared_ptr<T> FinedGameObject(std::string _className) {
		static_assert(std::is_base_of<object::GameObject, T>::value, "ゲームオブジェクトを継承してください");
		for (auto itr : m_gameObjectList) {
			if (itr->ClassName() == _className) {
				return std::static_pointer_cast<T>(itr);
				//return static_cast<std::shared_ptr<T>>();
			}
		}
		return nullptr;
	}

	//template<class T>
	//std::shared_ptr<T> GetGameObject(unsigned int _instanceNumber) {
	//	static_assert(std::is_base_of<object::GameObject, T>::value, "ゲームオブジェクトを継承してください");
	//	for (auto itr : m_gameObjectList) {
	//		if (itr->GetInstanceNumber() == _instanceNumber) {
	//			return itr;
	//		}
	//	}

	//	return nullptr;
	//}

	void DeleteGameObject(std::shared_ptr <object::GameObject>_eleteObject) {
		for (auto& itr : m_gameObjectList) {
			if (itr->m_incetanceNumber == _eleteObject->m_incetanceNumber) {
				itr = nullptr;
			}
		}
	}
	
	void Update();
	void FixedUpdate();

	void ShowImGui();

private:
	std::vector<object::GameObjectSPtr> m_gameObjectList;
	void TransformUpdate();
};

}
}

#endif  // GAME_OBEJCT_MANAGER_H_