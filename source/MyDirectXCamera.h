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

	//カメラの行列
	math::Matrix m_world_matrix;

	//カメラのプロジェクション行列
	math::Matrix m_projection_matrix;

	//カメラの逆行列
	math::Matrix m_invers_matrix;

	math::Vector3 m_eye;		// カメラ位置
	math::Vector3 m_look_at;		// 注視点
	math::Vector3 m_up;		// 上向きベクトル

	//プロジェクション行列生成用
	float			m_near;
	float			m_aspect;
	float			m_fov;
	float			m_far;

	//デバイス・デバイスコンテキスト
	directx::Device m_device;
	directx::DeviceContext m_device_context;

	std::weak_ptr<render::RenderTerget> m_renderTerget;

public:
	//コンストラクタ
	Camera(directx::Device _device, directx::DeviceContext _device_context);

	//初期化
	void Init(float _nearclip, float _farclip, float _fov, float _width, float _height, math::Vector3 _eye, math::Vector3 _lookat, math::Vector3 _up);

	//セッター
	void SetNear(float _nearclip);

	void SetFar(float _farclip);

	void SetFov(float _fov);

	void SetAspect(float _width, float _height);

	//プロジェクション行列設定
	void SetProjection(float _nearclip, float _farclip, float _fov, float _width, float _height);

	//カメラ目、注視点、上向きベクトル
	void SetCamera(const math::Vector3& _eye, const math::Vector3& _lookat, const math::Vector3& _up);

	//各自ベクトル設定
	void SetEye(const math::Vector3& _eye);

	void SetLookat(const math::Vector3& _look_at);

	void SetUp(const math::Vector3& _up);

	//カメラのマトリックスの生成
	void CreateCameraMatrix();

	//カメラのプロジェクションマトリックスの生成
	void CreateProjectionMatrix();

	//ゲッター
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