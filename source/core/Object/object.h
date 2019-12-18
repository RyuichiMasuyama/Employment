#pragma once

#ifndef OBEJCT_H_
#define OBEJCT_H_

#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include "./Math/Vector.h"
#include "./Math/Quaternion.h"

#define BASE_CLASS_IS(baseClass) using base = baseClass;

namespace mslib {

// �Q�[���I�u�W�F�N�g�̊Ǘ�
namespace manager {
class GameObjectManager;
}

namespace component {
class Component;
using ComponentSPtr = std::shared_ptr<Component>;
using ComponentPtr = std::weak_ptr<Component>;
}

namespace transform {

class Transform;
using TransformSPtr = std::shared_ptr<Transform>;
using TransformPtr = std::weak_ptr<Transform>;
}

namespace object {

class Object;
 using ObjectSPtr = std::shared_ptr<Object>;
 using ObjectPtr = std::weak_ptr<Object>;

 class TransformObejct;
 using TransformObejctSPtr= std::shared_ptr<TransformObejct>;
 using TransformObejctPtr = std::weak_ptr<TransformObejct>;

 class GameObject;
 using GameObjectSPtr = std::shared_ptr<GameObject>;
 using GameObjectPtr = std::weak_ptr<GameObject>;

class Object{
public:
	// �I�u�W�F�N�g�̏��������s������
	// �p�������N���X�ɂ�BASE_CLASS_IS���g����base��ݒ肳����
	// Initalazie�̒���base::Initialize()���s����
	virtual void Initialize() {};

	// InstanceNumber�𐶐�����A�_�E���L���X�g�̃R�X�g�_�E���ړI
	Object() { 
		static unsigned int _incetanceNumber = 0;
		m_incetanceNumber = _incetanceNumber;
		_incetanceNumber++;
	};
	virtual ~Object() = default;

	virtual void Update() = 0;
	virtual void ImGuiDraw() {};
protected:
	unsigned int m_incetanceNumber;
};


class TransformObejct :public Object{
	BASE_CLASS_IS(Object)
public:
	TransformObejct() : m_scale(1.f, 1.f, 1.f) {};
	~TransformObejct() = default;

	virtual void Initialize() {};

protected:
	// transform
	math::Vector3 m_position;
	math::Quaternion m_quaternion;
	math::Vector3 m_rotate;
	math::Vector3 m_scale;

	// �}�g���b�N�X
	math::Matrix m_matrix;

	unsigned int GetInstanceNumber() { return m_incetanceNumber; }
};

class GameObject :public TransformObejct {
	BASE_CLASS_IS(TransformObejct)
		friend manager::GameObjectManager;

public:
	static constexpr const char*  NonUpadteFunctionName = "NonUpadteFuntionName";

	GameObject();
	~GameObject() = default;

	virtual void Initialize();

	void Update();

	virtual void ImGuiDraw() {};

	// �Œ�t���[���A�b�v�f�[�g�̒ǉ�
	virtual void FixedUpdate();

	// �ǉ��̃R���|�[�l���g���A�^�b�`����B
	// �����ł�
	template<class T, class...LIST>
	std::weak_ptr<T> AddComponent(LIST&&... _list) {
		static_assert(std::is_base_of<component::Component, T>::value, "�Q�[���I�u�W�F�N�g���p�����Ă�������");
		auto result = std::make_shared<T>(_list...);

		result->m_transform = m_transform;
		m_component.push_back(result);
		result->Initialize();

		return result;
	};

	// �A�b�v�f�[�gFunction��ݒ肵�Ȃ��Ƃ�����ɔ��
	void NonUpdate() {}

private:
	std::vector<std::shared_ptr<component::Component>> m_component;

	std::unordered_map<std::string, std::function<void(void)>> m_function;

	std::string m_activeFunctionName = NonUpadteFunctionName;

	bool m_isActive = true;

	void TransformUpdate();
	void ChaildUpdate(const math::Matrix& _parentMat);

protected:
	template<typename T,class P>
	void CreateUpdateFunction(const std::string &_functionName, T&& _function, P _thisPtr) {
		m_function[_functionName] = std::bind(_function, _thisPtr);
	}

	void SetUpdateFunction(const std::string& _functionName) { m_activeFunctionName = _functionName; }

	void SetActive(const bool& _isActive) { m_isActive = _isActive; }
	const bool& GetActive() { return m_isActive; } 

	transform::TransformSPtr m_transform;

	virtual void BeforUpdate() {};
	virtual void AfterUpdate() {};

};

}

namespace component {
// �R���|�[�l���g�w��
class Component :public object::Object {
	friend object::GameObject;
	// friend transform::Transform;
	BASE_CLASS_IS(Object)
private:
	float m_priority;	// �D��x
	bool m_activeFlag;

public:
	virtual void Initialize() { 
		m_activeFlag = true;
	}
	Component() = default;
	virtual ~Component() = default;
	// MultiThread�œ���Update�͗D��x�����Ȃ��ƁA���s���ŏ�������܂��B
	// �D��x�ύX�֐����쐬����A�ύX���Ƀ\�[�g���s��
	// �D��x�̐ݒ��JobSystem���s���ׂ�����

	// �σt���[�����[�g
	// (SingleThread�œ����̂Œl�̎󂯓n���Ȃǂ�����ōs���ƈ��S)
	virtual void SingleThreadUpdate() {}
	// �σt���[�����[�g
	// (MultiThread�œ����̂ő����B�l�̎󂯓n���͊댯)
	virtual void Update() override {}
	// �Œ�t���[�����[�g
	// (MultiThread�œ����̂ő����B�l�̎󂯓n���͊댯)
	virtual void FixedUpdate() {}
	// �Œ�t���[�����[�g
	// (SingleThread�œ����̂Œl�̎󂯓n���͂�����ōs���ƈ��S)
	virtual void SingleThreadFixedUpdate() {}

	void SetActiveFlag(bool flag) { m_activeFlag = flag; }
	bool &IsAcive() { return m_activeFlag; }

protected:
	transform::TransformPtr m_transform;
};

}

namespace transform {

class Transform :public object::Object {
public:
	Transform(
		math::Vector3& _position,
		math::Quaternion& _quaternion,
		math::Vector3 _rotate,
		math::Vector3& _scale,
		math::Matrix& _matrix,
		object::GameObject* m_gameObject)
		:m_position(_position),
		m_quaternion(_quaternion),
		m_rotate(_rotate),
		m_scale(_scale),
		m_matrix(_matrix),
		m_gameObject(m_gameObject) {}

	TransformPtr m_parent;
	std::vector<TransformPtr> m_children;

	// from_this���g�������Ȃ��̂Ő��|��ێ�������
	// delete����Ȃ����S�z

	object::GameObject* m_gameObject;

	// �ʒu�E��]�E�T�C�Y
	math::Vector3& m_position;
	math::Quaternion& m_quaternion;
	math::Vector3& m_rotate;
	math::Vector3& m_scale;

	// �}�g���b�N�X
	math::Matrix& m_matrix;

	// �e�̐ݒ�
	void SetParent(TransformPtr _ptr);

	void Update() {}
};

}

}

#endif  // OBEJCT_H_
