#include "./core/Object/Object.h"

namespace mslib {
namespace object {

GameObject::GameObject() {
	m_transform = std::make_shared<transform::Transform>
		(m_position, m_quaternion, m_rotate, m_scale, m_matrix, this);
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

void GameObject::TransformUpdate() {
	if (m_transform->m_parent.expired()) ChaildUpdate(math::Matrix());
}

void GameObject::ChaildUpdate(const math::Matrix & _parentMat) {
	math::Matrix ans;
	
	// �T�C�Y
	ans.Scaling(m_scale);

	// ��]
	m_quaternion.Rotate(m_rotate);
	ans *= m_quaternion.GetMatrix();

	// �ʒu
	ans.MovePosition(m_position);

	// �e�q�֌W�Ȃ̂ł�����
	ans *= _parentMat;

	m_matrix = ans;

	for (auto itr : m_transform->m_children) {
		itr.lock()->m_gameObject->ChaildUpdate(m_matrix);
	}
}

}
namespace transform {

// case1: �e�����炸�A�ݒ肳�ꂽ�e�����Ȃ�
// case2: �e������A�ݒ肳�ꂽ�e������
// case3: �e�����炸�A�ݒ肳�ꂽ�e������
void Transform::SetParent(TransformPtr _ptr) {
	// ���g���Ȃ��inullptr�́j��
	if (_ptr.expired()) {
		if (m_parent.expired())return;	// case1
		// case2��
		auto itr = m_parent.lock()->m_children.begin();
		for (auto ptr : m_parent.lock()->m_children) {
			// �����������ꍇ
			if (ptr.lock()->m_incetanceNumber == m_incetanceNumber) {
				m_parent.lock()->m_children.erase(itr);
				break;
			}
			itr++;
		}
		// case2��
	}
	// ��������
	else {
		if (m_parent.expired()) {
			// case3��
			// �e�Ɏ�����o�^
			_ptr.lock()->m_children.push_back(_ptr);

			m_parent = _ptr;
			// case3��
		}
		else {
			// case4��
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
			// case4��
		}
	}

	m_parent.reset();
}

}
}
