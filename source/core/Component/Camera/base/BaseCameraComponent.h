#pragma once

#include "./Renderer/RenderTerget.h"
#include "./core/Object/Object.h"
#include "../../PostEffect/BasePostEffectComponent.h"

// �O���錾
namespace  mslib {
namespace render {
class RenderTerget;
}
}

namespace mslib {
namespace component {
class BaseCameraComponent;
using BaseCameraComponentPtr = std::weak_ptr<BaseCameraComponent>;
using BaseCameraComponentSPtr = std::shared_ptr<BaseCameraComponent>;

class BaseCameraComponent :public Component{
	BASE_CLASS_IS(Component)
	friend object::GameObject;
public:
	BaseCameraComponent();
	virtual ~BaseCameraComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override {
		CreateCameraMatrix();
	}

private:
	// �X�}�[�g�|�C���^�ŕێ�
	// �J�����̍s��
	std::shared_ptr<math::Matrix> m_worldMatrix;

	// �J�����̃v���W�F�N�V�����s��
	std::shared_ptr<math::Matrix> m_projectionMatrix;

	// �J�����̋t�s��
	std::shared_ptr<math::Matrix> m_inversMatrix;

	// �v���W�F�N�V�����s�񐶐��p
	std::shared_ptr<float> m_near;
	std::shared_ptr<float> m_aspect;
	std::shared_ptr<float> m_fov;
	std::shared_ptr<float> m_far;

	// ���_�̒���
	std::shared_ptr<float> m_length;

protected:
	// �V���������_�[�^�[�Q�b�g�𐶐�����
	std::weak_ptr<mslib::render::RenderTerget> m_renderTerget;	

public:
	// �Z�b�^�[
	void SetNear(float _nearclip);

	void SetFar(float _farclip);

	void SetFov(float _fov);

	void SetLength(float _lenght);

	void SetAspect(float _width, float _height);

	//�v���W�F�N�V�����s��ݒ�
	void SetProjection(float _nearclip, float _farclip, float _fov, float _width, float _height);

private:
	//�J�����̃}�g���b�N�X�̐���
	void CreateCameraMatrix();

	//�J�����̃v���W�F�N�V�����}�g���b�N�X�̐���
	void CreateProjectionMatrix();

	template<class T>
	std::weak_ptr<T> AddPostEffectComponent() {
		static_assert(std::is_base_of<component::BasePostEffectComponent, T>::value, "�|�X�g�G�t�F�N�g��ݒ肵�Ă�������");

		// �|�X�g�G�t�F�N�g�R���|�[�l���g�𐶐�
		// ����AAddComponent�ł̓|�X�g�G�t�F�N�g��
		// �A�^�b�`�ł��Ȃ��悤�ɂ��Ȃ���΂����Ȃ�
		auto postEffect = m_transform.lock()->m_gameObject.lock()->AddComponent<T>(m_renderTerget);
	}
};

}
}