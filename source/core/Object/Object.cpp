#include "./core/Object/Object.h"

namespace mslib {
namespace object {
std::string GameObject::ClassName() {
	return m_className;
}
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
	if (!m_isActive)return;
	for (auto itr : m_component) {
		itr->FixedUpdate();
	}
}

void GameObject::HitTriggerStay() {
	for (auto itr : m_component) {
		itr->HitTriggerStay();
	}
}

void GameObject::TransformUpdate() {
	if (m_transform->m_parent.expired()) ChaildUpdate(math::Matrix());
}

void GameObject::ChaildUpdate(const math::Matrix & _parentMat) {
	math::Matrix ans;
	
	// サイズ
	ans.Scaling(m_scale);

	// 回転
	m_quaternion.Rotate(m_rotate);
	ans *= m_quaternion.GetMatrix();

	// 位置
	ans.MovePosition(m_position);

	// AABB更新
	

	// 親子関係なのでかける
	ans *= _parentMat;

	m_matrix = ans;

	for (auto itr : m_transform->m_children) {
		itr.lock()->m_gameObject->ChaildUpdate(m_matrix);
	}
}

void GameObject::SetClassName(std::string _className) {
	m_className = _className;
}

}
namespace transform {

// case1: 親がおらず、設定された親もいない
// case2: 親がおり、設定された親がいる
// case3: 親がおらず、設定された親がいる
void Transform::SetParent(TransformPtr _ptr) {
	auto& myTrans = m_gameObject->m_transform;
	// 中身がない（nullptrの）時
	if (_ptr.expired()) {
		if (m_parent.expired())return;	// case1
		// case2↓
		auto itr = m_parent.lock()->m_children.begin();
		for (auto ptr : m_parent.lock()->m_children) {
			// 自分がいた場合
			if (ptr.lock()->m_incetanceNumber == m_incetanceNumber) {
				m_parent.lock()->m_children.erase(itr);
				break;
			}
			itr++;
		}
		// case2↑
	}
	// あった時
	else {
		if (m_parent.expired()) {
			// case3↓
			// 親に自分を登録
			_ptr.lock()->m_children.push_back(myTrans);

			m_parent = _ptr;
			// case3↑
		}
		else {
			// case4↓
			auto itr = m_parent.lock()->m_children.begin();
			for (auto ptr : m_parent.lock()->m_children) {
				// 自分がいた場合
				if (ptr.lock()->m_incetanceNumber == m_incetanceNumber) {
					m_parent.lock()->m_children.erase(itr);
					break;
				}
				itr++;
			}
			// 親に自分を登録
			_ptr.lock()->m_children.push_back(_ptr);

			m_parent = _ptr;
			// case4↑
		}
	}

	//m_parent.reset();
}

}
namespace component {
transform::TransformPtr Component::GetTransform() {
	return m_transform;
}
}
}

