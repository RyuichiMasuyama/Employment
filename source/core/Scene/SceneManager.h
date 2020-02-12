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
		static_assert(std::is_base_of<BaseScene, T>::value , "CreateScene�̓V�[�����p�������N���X���������ł��܂���B");

		if (_sceneElase) {
			while (!m_scenes.empty()) {
				m_scenes.top()->UnLoad();
				m_scenes.pop();
			}
		}

		// ����
		auto scene = std::make_unique<T>();

		// ���[�h
		scene->Load();
		if (m_scenes.size() != 0)
			m_scenes.top()->UnActive();

		// �L���[�ɑ��
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