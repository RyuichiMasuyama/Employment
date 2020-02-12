#pragma once

#include <./core/Object/object.h>

namespace mslib {
namespace component {
class FieldManagerComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	FieldManagerComponent(bool& _enemyEnter);
	~FieldManagerComponent() = default;

	void Initialize() override;
	void FixedUpdate() override;
private:
	const bool& m_enemyEnter;
};
}
}