#include "./directx/SubResourceSendManager.h"
#include "./DirectX/DirectX11Manager.h"

namespace mslib {
//namespace Transform {
//void TransformSendContext::Init(mslib::directx::Device _device, mslib::directx::DeviceContext _device_context)
//{
//	m_device = _device, m_device_context = _device_context;
//
//	directx::BufferCreater m_buffer_creater(_device);
//
//	m_world_constant = m_buffer_creater.CreateConstantBuffer(sizeof(ConstantBufferWorld));
//	m_view_constant = m_buffer_creater.CreateConstantBuffer(sizeof(ConstantBufferView));
//	m_projection_constant = m_buffer_creater.CreateConstantBuffer(sizeof(ConstantBufferProjection));
//
//}
//
//void TransformSendContext::SendTransform(const math::Matrix & _matrix, TYPE _type)
//{
//	switch (_type) {
//	case TYPE::WORLD:
//		m_update_world.world = _matrix;//= DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&_matrix));
//		m_device_context->UpdateSubresource(m_world_constant.Get(), 0, nullptr, &m_update_world, 0, 0);
//		m_device_context->VSSetConstantBuffers(0, 1, m_world_constant.GetAddressOf());
//		m_device_context->PSSetConstantBuffers(0, 1, m_world_constant.GetAddressOf());
//		break;
//	case TYPE::VIEW:
//		m_update_view.view = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&_matrix));
//		m_device_context->UpdateSubresource(m_view_constant.Get(), 0, nullptr, &m_update_view, 0, 0);
//		m_device_context->VSSetConstantBuffers(1, 1, m_view_constant.GetAddressOf());
//		m_device_context->PSSetConstantBuffers(1, 1, m_view_constant.GetAddressOf());
//		break;
//	case TYPE::PROJECTION:
//		m_update_projection.projection = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&_matrix));
//		m_device_context->UpdateSubresource(m_projection_constant.Get(), 0, nullptr, &m_update_projection, 0, 0);
//		m_device_context->VSSetConstantBuffers(2, 1, m_projection_constant.GetAddressOf());
//		m_device_context->PSSetConstantBuffers(2, 1, m_projection_constant.GetAddressOf());
//		break;
//	}
//}
//
//
//}
namespace directx {

SubResourceSendManager::SubResourceSendManager() {
	Initialize();
}

void SubResourceSendManager::Initialize() {
	directx::BufferCreater m_buffer_creater;

	m_worldObjectBuffer = m_buffer_creater.CreateConstantBuffer(sizeof(WorldObjectBuffer));;
	m_cameraObjectBuffer = m_buffer_creater.CreateConstantBuffer(sizeof(CameraObejctBuffer));
	m_materialObjectBuffer = m_buffer_creater.CreateConstantBuffer(sizeof(MaterialObjectBuffer));
	m_lightObjectBuffer = m_buffer_creater.CreateConstantBuffer(sizeof(LightObjectBuffer));
	m_timeBuffer = m_buffer_creater.CreateConstantBuffer(sizeof(TimeBuffer));
	m_postEffectBuffer= m_buffer_creater.CreateConstantBuffer(sizeof(PostEffectBuffer));

	m_deviceContext = DirectX11Manager::GetInstance().GetDeviceContext();
}

void directx::SubResourceSendManager::SetWorldObjectBuffer(const math::Matrix & _world) {
	auto xmmat = _world;

	m_worldObject.world = xmmat.ToMATRIX();
	m_deviceContext->UpdateSubresource(m_worldObjectBuffer.Get(), 0, nullptr, &m_worldObject, 0, 0);
	m_deviceContext->VSSetConstantBuffers(0, 1, m_worldObjectBuffer.GetAddressOf());
	m_deviceContext->PSSetConstantBuffers(0, 1, m_worldObjectBuffer.GetAddressOf());
}

void SubResourceSendManager::SetCameraObjectBuffer(
	const math::Matrix & _view,
	const math::Matrix & _projection,
	const math::Matrix & _invers,
	const math::Vector4 & _position) {
	auto xmmat = _view;
	m_cameraObject.view = xmmat.ToMATRIX();
	xmmat = _projection;
	m_cameraObject.projection = xmmat.ToMATRIX();
	xmmat = _invers;
	m_cameraObject.invers = xmmat.ToMATRIX();
	m_cameraObject.position = _position;
	m_deviceContext->UpdateSubresource(m_cameraObjectBuffer.Get(), 0, nullptr, &m_cameraObject, 0, 0);
	m_deviceContext->VSSetConstantBuffers(1, 1, m_cameraObjectBuffer.GetAddressOf());
	m_deviceContext->PSSetConstantBuffers(1, 1, m_cameraObjectBuffer.GetAddressOf());
}

void SubResourceSendManager::SetMaterialBuffer(
	const math::Vector4& _ambient,
	const math::Vector4& _diffuse,
	const math::Vector4& _emissive,
	const math::Vector4& _bump,
	const math::Vector4& _specular,
	const float& _transparency,
	const float& _shininess,
	const float& _reflectivity) {
	m_materialObject.ambient = _ambient;
	m_materialObject.diffuse = _diffuse;
	m_materialObject.emissive = _emissive;
	m_materialObject.bump = _bump;
	m_materialObject.specular = _specular;
	m_materialObject.sub.x = _transparency;
	m_materialObject.sub.y = _shininess;
	m_materialObject.sub.z = _reflectivity;
	m_deviceContext->UpdateSubresource(m_materialObjectBuffer.Get(), 0, nullptr, &m_materialObject, 0, 0);
	m_deviceContext->VSSetConstantBuffers(2, 1, m_materialObjectBuffer.GetAddressOf());
	m_deviceContext->PSSetConstantBuffers(2, 1, m_materialObjectBuffer.GetAddressOf());
}
void SubResourceSendManager::SetMaterialBuffer(const render::Material* _material) {
	m_materialObject.ambient = math::Vector4(_material->ambient);
	m_materialObject.diffuse = math::Vector4(_material->diffuse);
	m_materialObject.emissive = math::Vector4(_material->emissive);
	m_materialObject.bump = math::Vector4(_material->bump);
	m_materialObject.specular = _material->specular;
	m_materialObject.sub.x = _material->transparency;
	m_materialObject.sub.y = _material->shininess;
	m_materialObject.sub.z = _material->reflectivity;
	m_deviceContext->UpdateSubresource(m_materialObjectBuffer.Get(), 0, nullptr, &m_materialObject, 0, 0);
	m_deviceContext->VSSetConstantBuffers(2, 1, m_materialObjectBuffer.GetAddressOf());
	m_deviceContext->PSSetConstantBuffers(2, 1, m_materialObjectBuffer.GetAddressOf());
};
void SubResourceSendManager::SetLightBuffer(
	const math::Vector4 & _way,
	const math::Vector4& _color) {
	m_lightObject.way = _way;
	m_lightObject.color = _color;
	m_deviceContext->UpdateSubresource(m_lightObjectBuffer.Get(), 0, nullptr, &m_lightObject, 0, 0);
	m_deviceContext->VSSetConstantBuffers(3, 1, m_lightObjectBuffer.GetAddressOf());
	m_deviceContext->PSSetConstantBuffers(3, 1, m_lightObjectBuffer.GetAddressOf());
}

void SubResourceSendManager::SetTimeBuffer(
	const math::Vector4 & _time,
	const math::Vector4 & _deltaTime) {
	m_time.myTime = _time;
	m_time.myDeltaTime = _deltaTime;
	m_deviceContext->UpdateSubresource(m_timeBuffer.Get(), 0, nullptr, &m_time, 0, 0);
	m_deviceContext->VSSetConstantBuffers(4, 1, m_timeBuffer.GetAddressOf());
	m_deviceContext->PSSetConstantBuffers(4, 1, m_timeBuffer.GetAddressOf());
}

void SubResourceSendManager::SetPostEffect(
	const std::array<float, 8>& _gauss,
	const std::array<float, 8>& _bloomDiffuse,
	const float& _bloomSpecular) {
	m_postEffect.gausse1 = math::Vector4(_gauss[0], _gauss[1], _gauss[2], _gauss[3]);
	m_postEffect.gausse2 = math::Vector4(_gauss[4], _gauss[5], _gauss[6], _gauss[7]);
	// m_postEffect.bloom = _bloom;
	m_deviceContext->UpdateSubresource(m_postEffectBuffer.Get(), 0, nullptr, &m_postEffect, 0, 0);
	m_deviceContext->VSSetConstantBuffers(5, 1, m_postEffectBuffer.GetAddressOf());
	m_deviceContext->PSSetConstantBuffers(5, 1, m_postEffectBuffer.GetAddressOf());
}

}
}