#pragma once

#include "./core/base.h"
#include "../Object/Object.h"

#include <vector>

namespace mslib {
namespace scene {

// シーンはすべてこれを継承する
class BaseScene :public mslib::core::base {

private:
	std::vector<object::ObjectPtr> m_object;

public:
	// 必須関数
	virtual void Update() = 0;

	// 任意関数
	// ロード
	virtual void ImGuiDraw() {};	// 現在使用予定はない
	virtual void Draw() {};			// 現在使用予定はない
	virtual void Load() {};
	virtual void UnLoad() {};

protected:
	void AllObjectUpdate();		// 全体のアップデート
	void AllImGuiDraw();		// 全体のImGuiの描画
	void IncetanceObject(object::ObjectPtr _object); // 生成したオブジェクトを入れる
};

}
}