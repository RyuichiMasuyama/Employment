#pragma once

#include "./core/Object/object.h"

#include "../../core/Input/Input.h"

namespace mslib {
namespace object {

// 前方宣言
class TitleSceneManagerGameObject;
using TitleSceneManagerGameObjectPtr = std::weak_ptr<TitleSceneManagerGameObject>;
using TitleSceneManagerGameObjectSPtr = std::shared_ptr<TitleSceneManagerGameObject>;



class TitleSceneManagerGameObject :public object::GameObject{
	BASE_CLASS_IS(object::GameObject)
	static constexpr const char* OBJECT_NAME = "TitleSceneManagerGameObject";
public:
	// コンストラクタ・デストラクタ
	TitleSceneManagerGameObject() = default;
	~TitleSceneManagerGameObject() = default;

	// 初期化
	void Initialize()override {
		base::Initialize();

		// 初期化
		m_pushAnyKey = false;
	};

	// 可変アップデート
	void Update() override{

		if (input::Input::GetAnyEnter()) {
			m_pushAnyKey = true;
		}
	}

private:
	// キーを押されたらtrueに
	bool m_pushAnyKey;
};
}
}