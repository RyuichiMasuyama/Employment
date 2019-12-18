#pragma once

#include "./core/Object/object.h"

namespace mslib {
namespace origin {
namespace manager {

class RpgManagerComponent;
using RpgManagerComponentPtr = std::weak_ptr<RpgManagerComponent>;
using RpgManagerComponentSPtr = std::shared_ptr<RpgManagerComponent>;

// PHASE�Ǘ�
// �I���t���O
class RpgManagerComponent :public component::Component {
	BASE_CLASS_IS(Component)
public:

	RpgManagerComponent(int _battlePhase);
	~RpgManagerComponent() = default;

	void Initialize() override;
	void Update() override;

private:
	// �o�g���t�F�[�Y���Ǘ�����
	int m_battlePhase;

};

}  // namespace game
}  // namespace orign
}  // namespace mslib