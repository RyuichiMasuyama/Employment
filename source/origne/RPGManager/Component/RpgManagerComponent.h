#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace origin {
namespace manager {

class RpgManagerComponent;
using RpgManagerComponentPtr = std::weak_ptr<RpgManagerComponent>;
using RpgManagerComponentSPtr = std::shared_ptr<RpgManagerComponent>;

// PHASE管理
// 終了フラグ
class RpgManagerComponent :public component::Component {
	BASE_CLASS_IS(Component)
public:

	RpgManagerComponent(int _battlePhase);
	~RpgManagerComponent() = default;

	void Initialize() override;
	void Update() override;

private:
	// バトルフェーズを管理する
	int m_battlePhase;

};

}  // namespace game
}  // namespace orign
}  // namespace mslib