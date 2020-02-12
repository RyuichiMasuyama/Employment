#pragma once

#include "./BaseScene.h"
#include "./Singleton.h"

// #include "./TestScene.h"
#include <memory>
#include <stack>

namespace mslib {
namespace scene {

class SceneManager:public pattern::Singleton< SceneManager >{
public:
	void Update();
	void Draw();
	void ImGuiDraw();

	template<class T>
	void CreateScene(bool _sceneElase = false) {
		static_assert(std::is_base_of<BaseScene, T>::value , "CreateSceneはシーンを継承したクラスしか生成できません。");

		if (_sceneElase) {
			while (!m_scenes.empty()) {
				m_scenes.top()->UnLoad();
				m_scenes.pop();
			}
		}

		// 生成
		auto scene = std::make_unique<T>();

		// ロード
		scene->Load();
		if (m_scenes.size() != 0)
			m_scenes.top()->UnActive();

		// キューに代入
		m_scenes.push(std::move(scene));

	};

	void PopScene() {
		if (!m_scenes.empty()) {
			m_scenes.top()->UnLoad();
			m_scenes.pop();
			m_scenes.top()->OnActive();
		}
	}

	std::stack<std::unique_ptr<BaseScene>> m_scenes;
};

}
}