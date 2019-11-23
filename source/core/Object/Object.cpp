#include "./core/Object/Object.h"

namespace mslib {
namespace object {

GameObject::GameObject() {
	m_transform = std::make_shared<transform::Transform>
		(m_position, m_quaternion, m_scale, m_matrix);
}

void GameObject::Initialize() {
	base::Initialize();

	CreateUpdateFunction(NonUpadteFunctionName, &GameObject::NonUpdate ,this);
}

void GameObject::Update() {
	if (!m_isActive)return;

	BeforUpdate();

	for (auto itr : m_component) {
		itr->Update();
	}

	m_function[m_activeFunctionName]();
	
	AfterUpdate();
}

void GameObject::FixedUpdate() {
	for (auto itr : m_component) {
		itr->FixedUpdate();
	}
}

}
namespace transform {
void Transform::SetParent(TransformPtr _ptr) {
	// ���g���Ȃ��inullptr�́j��
	if (_ptr.expired()) {
		auto itr = m_parent.lock()->m_children.begin();
		for (auto ptr : m_parent.lock()->m_children) {
			// �����������ꍇ
			if (ptr.lock()->m_incetanceNumber == m_incetanceNumber) {
				m_parent.lock()->m_children.erase(itr);
				break;
			}
			itr++;
		}
	}
	// ��������
	else {
		if (m_parent.expired()) {
			// �e�Ɏ�����o�^
			_ptr.lock()->m_children.push_back(_ptr);

			m_parent = _ptr;
		}
		else {
			auto itr = m_parent.lock()->m_children.begin();
			for (auto ptr : m_parent.lock()->m_children) {
				// �����������ꍇ
				if (ptr.lock()->m_incetanceNumber == m_incetanceNumber) {
					m_parent.lock()->m_children.erase(itr);
					break;
				}
				itr++;
			}
			// �e�Ɏ�����o�^
			_ptr.lock()->m_children.push_back(_ptr);

			m_parent = _ptr;
		}
	}

	m_parent.reset();
}

}
}
