#pragma once

#include "./core/base.h"
#include "../Object/Object.h"
#include "./origne/Camera/HaveCameraGameObject.h"
#include <./GameObjectManager.h>

#include <vector>

namespace mslib {
namespace scene {

// シーンはすべてこれを継承する
class BaseScene :public mslib::core::base {

private:
	std::vector<object::ObjectSPtr> m_object;

public:
	// 必須関数
	virtual void Update() = 0;

	// 任意関数
	// ロード
	virtual void ImGuiDraw() {};	// 現在使用予定はない
	virtual void Draw() {};			// 現在使用予定はない
	virtual void Load() {};
	virtual void UnLoad() {};

	virtual void UnActive() {};		// 新しいシーンを読み込み、今のシーンがstackされたとき
	virtual void OnActive() {};		// 上のシーンがUnLoadされたとき
protected:
	void AllObjectUpdate();		// 全体のアップデート
	void AllImGuiDraw();		// 全体のImGuiの描画
	void IncetanceObject(object::ObjectSPtr _object); // 生成したオブジェクトを入れる

	// object::HaveCameraGameObjectSPtr m_haveCamera;
};

}
}