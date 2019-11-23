#include "BaseScene.h"
#include <algorithm>

namespace mslib {
namespace scene {

// 全部のオブジェクトのアップデート優先度など今は無し
// オブジェクトの中身が消えていたら破棄もする
void BaseScene::AllObjectUpdate() {
	// CreanUp
	std::vector<object::ObjectPtr> result;
	for (auto itr: m_object) {
		if (!itr.expired()) {
			result.push_back(itr);
		}
	}

	// Update
	for (auto itr : m_object) {
		itr.lock()->Update();
	}
}

void BaseScene::AllImGuiDraw() {
	// ImGuiの描画
	for (auto itr : m_object) {
		itr.lock()->ImGuiDraw();
	}
}

// オブジェクトの追加・ロード関数内で使う予定
void BaseScene::IncetanceObject(object::ObjectPtr _object) {
	m_object.push_back(_object);
}

}
}