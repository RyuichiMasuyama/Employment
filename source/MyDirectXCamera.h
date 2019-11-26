#pragma once

#include "MyDirectXMath.h"
#include "./DirectX/DirectX11Manager.h"

namespace mslib {
namespace render {
class RenderTerget;
}

namespace Camera {

class Camera {
private:
	struct CameraConstantBuffer
	{
		math::Vector4 camera_eye;
		math::Matrix camera_invers;
	};

	mslib::directx::ConstantBuffer m_constant_buffer_camera;

	//�J�����̍s��
	math::Matrix m_world_matrix;

	//�J�����̃v���W�F�N�V�����s��
	math::Matrix m_projection_matrix;

	//�J�����̋t�s��
	math::Matrix m_invers_matrix;

	math::Vector3 m_eye;		// �J�����ʒu
	math::Vector3 m_look_at;		// �����_
	math::Vector3 m_up;		// ������x�N�g��

	//�v���W�F�N�V�����s�񐶐��p
	float			m_near;
	float			m_aspect;
	float			m_fov;
	float			m_far;

	//�f�o�C�X�E�f�o�C�X�R���e�L�X�g
	directx::Device m_device;
	directx::DeviceContext m_device_context;

	std::weak_ptr<render::RenderTerget> m_renderTerget;

public:
	//�R���X�g���N�^
	Camera(directx::Device _device, directx::DeviceContext _device_context);

	//������
	void Init(float _nearclip, float _farclip, float _fov, float _width, float _height, math::Vector3 _eye, math::Vector3 _lookat, math::Vector3 _up);

	//�Z�b�^�[
	void SetNear(float _nearclip);

	void SetFar(float _farclip);

	void SetFov(float _fov);

	void SetAspect(float _width, float _height);

	//�v���W�F�N�V�����s��ݒ�
	void SetProjection(float _nearclip, float _farclip, float _fov, float _width, float _height);

	//�J�����ځA�����_�A������x�N�g��
	void SetCamera(const math::Vector3& _eye, const math::Vector3& _lookat, const math::Vector3& _up);

	//�e���x�N�g���ݒ�
	void SetEye(const math::Vector3& _eye);

	void SetLookat(const math::Vector3& _look_at);

	void SetUp(const math::Vector3& _up);

	//�J�����̃}�g���b�N�X�̐���
	void CreateCameraMatrix();

	//�J�����̃v���W�F�N�V�����}�g���b�N�X�̐���
	void CreateProjectionMatrix();

	//�Q�b�^�[
	const math::Matrix& GetCameraMatrix()const;

	const math::Matrix& GetCameraMatrixInvers()const;

	const math::Matrix& GetProjectionMatrix()const;

	float GetFov() const;

	const math::Vector3& GetEye() const;

	const math::Vector3& GetLookat() const;

	const math::Vector3& GetUp() const;

	void Update();
};
}
}