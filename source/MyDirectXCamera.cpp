#include "MyDirectXCamera.h"
#include "./Shader/Shader.h"
#include "./DirectX/SubResourceSendManager.h"

namespace mslib {
namespace Camera {

Camera::Camera(directx::Device _device, directx::DeviceContext _device_context)
	:m_device(_device), m_device_context(_device_context) {
	directx::BufferCreater buffer_creater(_device);

	m_constant_buffer_camera.Attach(buffer_creater.CreateConstantBuffer(sizeof(CameraConstantBuffer)));

	m_renderTerget = mslib::render::RenderTergetManager::GetInstance().CreateRenderTerget(mslib::render::RenderTergetType::SUBCAMERA);
}

void Camera::Init(
	float _nearclip, float _farclip, float _fov, float _width, float _height,
	math::Vector3 _eye, math::Vector3 _lookat, math::Vector3 _up) {
	SetProjection(_nearclip, _farclip, _fov, _width, _height);
	SetCamera(_eye, _lookat, _up);
}

void Camera::SetNear(float _nearclip) {
	m_near = _nearclip;
}

void Camera::SetFar(float _farclip) {
	m_far = _farclip;
}

void Camera::SetFov(float _fov) {
	m_fov = _fov;
}

void Camera::SetAspect(float _width, float _height) {
	m_aspect = _width / _height;
}

void Camera::SetProjection(float _nearclip, float _farclip, float _fov, float _width, float _height) {
	SetNear(_nearclip);
	SetFar(_farclip);
	SetFov(_fov);
	SetAspect(_width, _height);
	CreateProjectionMatrix();
}

void Camera::SetCamera(const math::Vector3 & _eye, const math::Vector3 & _lookat, const math::Vector3 & _up) {
	SetEye(_eye);
	SetLookat(_lookat);
	SetUp(_up);
	CreateCameraMatrix();
}

void Camera::SetEye(const math::Vector3 & _eye) {
	m_eye = _eye;
}

void Camera::SetLookat(const math::Vector3 & _look_at) {
	m_look_at = _look_at;
}

void Camera::SetUp(const math::Vector3 & _up) {
	m_up = _up;
}

void Camera::CreateCameraMatrix() {
	ALIGN16 DirectX::XMVECTOR eye = DirectX::XMVectorSet(m_eye.x, m_eye.y, m_eye.z, 0.0f);
	ALIGN16 DirectX::XMVECTOR at = DirectX::XMVectorSet(m_look_at.x, m_look_at.y, m_look_at.z, 0.0f);
	ALIGN16 DirectX::XMVECTOR up = DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f);

	ALIGN16 DirectX::XMMATRIX camera;
	camera = DirectX::XMMatrixLookAtLH(eye, at, up);

	XMStoreFloat4x4(&m_world_matrix, camera);
}

void Camera::CreateProjectionMatrix() {
	ALIGN16 DirectX::XMMATRIX projection;

	projection = DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_near, m_far);

	XMStoreFloat4x4(&m_projection_matrix, projection);
}

const math::Matrix & Camera::GetCameraMatrix() const {
	return m_world_matrix;
}

const math::Matrix & Camera::GetCameraMatrixInvers() const {
	return m_invers_matrix;
}

const math::Matrix & Camera::GetProjectionMatrix() const {
	return m_projection_matrix;
}

float Camera::GetFov() const {
	return m_fov;
}

const math::Vector3 & Camera::GetEye() const {
	return m_eye;
}

const math::Vector3 & Camera::GetLookat() const {
	return m_look_at;
}

const math::Vector3 & Camera::GetUp() const {
	return m_up;
}

void Camera::Update() {

	CameraConstantBuffer cons_camera;

	cons_camera.camera_eye.x = m_eye.x;
	cons_camera.camera_eye.y = m_eye.y;
	cons_camera.camera_eye.z = m_eye.z;
	cons_camera.camera_eye.w = 0.f;

	m_invers_matrix = math::Matrix::Inverse(m_world_matrix);

	cons_camera.camera_invers = m_invers_matrix;

	m_device_context->UpdateSubresource(m_constant_buffer_camera.Get(),
		0,
		nullptr,
		&cons_camera,
		0, 0);

	//コンスタントバッファ4をｂ6レジスタへセット（頂点シェーダー用）
	m_device_context->VSSetConstantBuffers(6, 1, m_constant_buffer_camera.GetAddressOf());
	//コンスタントバッファ4をｂ6レジスタへセット(ピクセルシェーダー用)
	m_device_context->PSSetConstantBuffers(6, 1, m_constant_buffer_camera.GetAddressOf());

	//カメラのデバイスを送る
	Transform::TransformSendContext::GetInstance().SendTransform(m_world_matrix, Transform::TransformSendContext::TYPE::VIEW);
	Transform::TransformSendContext::GetInstance().SendTransform(m_projection_matrix, Transform::TransformSendContext::TYPE::PROJECTION);
}

}
}