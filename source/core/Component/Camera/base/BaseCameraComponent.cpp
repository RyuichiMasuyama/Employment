#include "./BaseCameraComponent.h"
#include "./Renderer/RenderTerget.h"

namespace mslib {
namespace component {
BaseCameraComponent::BaseCameraComponent() {
	// 各変数の生成
	// nullチェックを入れたいのでシェアードポインタ化
	// カメラの行列
	m_worldMatrix = std::make_shared<math::Matrix>();

	// カメラのプロジェクション行列
	m_projectionMatrix = std::make_shared<math::Matrix>();

	// カメラの逆行列
	m_inversMatrix = std::make_shared<math::Matrix>();

	// プロジェクション行列生成用
	m_near = std::make_shared<float>();
	m_aspect = std::make_shared<float>();
	m_fov = std::make_shared<float>();
	m_far = std::make_shared<float>();

	// 視点の長さ
	m_length = std::make_shared<float>();
}

void BaseCameraComponent::Initialize() {
	base::Initialize();
	// ポインタを渡しておく
	m_renderTerget.lock()->SetCameraData(
		m_worldMatrix,
		m_projectionMatrix,
		m_inversMatrix,
		&m_transform.lock()->m_position);
}
void BaseCameraComponent::SetNear(float _nearclip) {
	*m_near = _nearclip;
}

void BaseCameraComponent::SetFar(float _farclip) {
	*m_far = _farclip;
}

void BaseCameraComponent::SetFov(float _fov) {
	*m_fov = _fov;
}

void BaseCameraComponent::SetLength(float _lenght) {
	*m_length = _lenght;
	CreateCameraMatrix();
}

void BaseCameraComponent::SetAspect(float _width, float _height) {
	*m_aspect = _width / _height;
}

void BaseCameraComponent::SetProjection(
	float _nearclip,
	float _farclip,
	float _fov,
	float _width,
	float _height) {
	SetNear(_nearclip);
	SetFar(_farclip);
	SetFov(_fov);
	SetAspect(_width, _height);
	CreateProjectionMatrix();
}

void BaseCameraComponent::CreateCameraMatrix() {
	auto pos = m_transform.lock()->m_position;
	auto mat = m_transform.lock()->m_matrix;
	auto look = mat.GetFront() * *m_length + pos;
	auto upVec = mat.GetUp();

	ALIGN16 DirectX::XMVECTOR eye = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.0f);
	ALIGN16 DirectX::XMVECTOR at = DirectX::XMVectorSet(look.x, look.y, look.z, 0.0f);
	ALIGN16 DirectX::XMVECTOR up = DirectX::XMVectorSet(upVec.x, upVec.y, upVec.z, 0.0f);

	ALIGN16 DirectX::XMMATRIX camera;
	math::Matrix getMat;
	camera = DirectX::XMMatrixLookAtLH(eye, at, up);

	XMStoreFloat4x4(&mat, camera); 
	*m_worldMatrix = mat;
}
 
void BaseCameraComponent::CreateProjectionMatrix() {
	ALIGN16 DirectX::XMMATRIX projection;

	projection = DirectX::XMMatrixPerspectiveFovLH(*m_fov,*m_aspect, *m_near, *m_far);

	math::Matrix mat;
	XMStoreFloat4x4(&mat, projection);
	*m_projectionMatrix = mat;
}

}
}

