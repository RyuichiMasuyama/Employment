#pragma once

#include "./MyDirectXMath.h"
#include "./DirectX/DirectX11Manager.h"
#include "./Shader/Shader.h"
#include "./Singleton.h"

namespace mslib {
namespace Transform {
class TransformSendContext :public pattern::Singleton<TransformSendContext> {
private:
	struct ConstantBufferWorld
	{
		DirectX::XMMATRIX world;
	};

	struct ConstantBufferView
	{
		DirectX::XMMATRIX view;
	};

	struct ConstantBufferProjection
	{
		DirectX::XMMATRIX projection;
	};

	//コンスタントバッファ
	mslib::directx::ConstantBuffer m_world_constant;
	mslib::directx::ConstantBuffer m_view_constant;
	mslib::directx::ConstantBuffer m_projection_constant;

	//更新用バッファ
	ConstantBufferWorld m_update_world;
	ConstantBufferView m_update_view;
	ConstantBufferProjection m_update_projection;

	mslib::directx::Device m_device;
	mslib::directx::DeviceContext m_device_context;

public:
	enum class TYPE {
		WORLD,
		VIEW,
		PROJECTION
	};

	void Init(mslib::directx::Device _device, mslib::directx::DeviceContext _device_context);

	void SendTransform(const math::Matrix& _matrix, TYPE _type);
};
}	// namespace Transform

namespace directx{
class SubResourceSendManager :public pattern::Singleton<SubResourceSendManager> {
private:
	// register b0	// 1オブジェクトに一つ
	struct WorldObjectBuffer {
		DirectX::XMFLOAT4X4 world;
	};

	// register b1　// カメラレンダーターゲットに一つ
	struct CameraObejctBuffer {
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
		DirectX::XMFLOAT4X4 invers;
		DirectX::XMFLOAT4 position;
	};
	
	// register b2　// 1オブジェクトに一つ
	struct MaterialObjectBuffer {
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 diffuse;
		DirectX::XMFLOAT4 specular;
	};

	// register b3　// 世界に多数？
	struct LightObjectBuffer {
		DirectX::XMFLOAT4 way;
		DirectX::XMFLOAT4 color;
	};

	// register b4 // 世界に一つ(Update内に渡せばいいと思う)
	struct TimeBuffer {
		DirectX::XMFLOAT4 myTime;
		DirectX::XMFLOAT4 myDeltaTime;
	};

	// 実数構造体
	WorldObjectBuffer m_worldObject;
	CameraObejctBuffer m_cameraObject;
	MaterialObjectBuffer m_materialObject;
	LightObjectBuffer m_lightObject;
	TimeBuffer m_time;

	// コンスタントバッファ
	ConstantBuffer m_worldObjectBuffer;
	ConstantBuffer m_cameraObjectBuffer;
	ConstantBuffer m_materialObjectBuffer;
	ConstantBuffer m_lightObjectBuffer;
	ConstantBuffer m_timeBuffer;

	DeviceContext m_deviceContext;

public:
	void Initialize();

	void SetWorldObjectBuffer(const math::Matrix& _world);
	void SetCameraObjectBuffer(
		const math::Matrix& _view,
		const math::Matrix& _projection,
		const math::Matrix& _invers,
		const math::Vector4& _position);
	void SetMaterialBuffer(
		const math::Vector4& _ambient,
		const math::Vector4& _diffuse,
		const math::Vector4& _specular);
	void SetLightBuffer(
		const math::Vector4& _way,
		const math::Vector4& _color);
	void SetTimeBuffer(
		const math::Vector4& _time, 
		const math::Vector4& _deltaTime);
};

}	// namespace directx
}	// namespace mslib