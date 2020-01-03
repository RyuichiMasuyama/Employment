#pragma once

#include "./core/Object/object.h"

#include "../../core/Input/Input.h"
namespace mslib {
namespace object {

// 前方宣言
class TitleSceneManagerGameObject;
using TitleSceneManagerGameObjectPtr = std::weak_ptr<TitleSceneManagerGameObject>;
using TitleSceneManagerGameObjectSPtr = std::shared_ptr<TitleSceneManagerGameObject>;

class HaveCameraGameObject;
using HaveCameraGameObjectPtr = std::weak_ptr<HaveCameraGameObject>;

class TitleSceneManagerGameObject :public object::GameObject{
	BASE_CLASS_IS(object::GameObject)
	static constexpr const char* OBJECT_NAME = "TitleSceneManagerGameObject";
public:
	// コンストラクタ・デストラクタ
	TitleSceneManagerGameObject(HaveCameraGameObjectPtr _haveCameraObjectPtr);
	~TitleSceneManagerGameObject() = default;

	// 初期化
	void Initialize()override;

	// 可変アップデート
	void Update() override;

private:
	// キーを押されたらtrueに
	bool m_pushAnyKey;

	float m_feadLevel;

	// カメラを持っているゲームオブジェクトのポインタ
	HaveCameraGameObjectPtr m_haveCameraGameObjectPtr;
};
}
}