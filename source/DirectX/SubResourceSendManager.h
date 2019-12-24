#pragma once

#include "./MyDirectXMath.h"
#include "./DirectX/DirectX11Manager.h"
#include "./Renderer/RenderObject.h"
#include <Singleton.h>
#include <array>

// もう一段階ラッピングをしたい
// ラッピングをすると同時にSingletonの解除も
// たぶんstaticになると予想される

namespace mslib {
namespace directx{
class SubResourceSendManager :public pattern::Singleton<SubResourceSendManager> {
public:
	static constexpr int LIGHT_MAX = 100;
private:	
	// register b0	// 1オブジェクトに一つ
	struct WorldObjectBuffer {
		DirectX::XMMATRIX world;
	};

	// register b1　// カメラレンダーターゲットに一つ
	struct CameraObejctBuffer {
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		DirectX::XMMATRIX invers;
		DirectX::XMFLOAT4 position;
		DirectX::XMMATRIX shadow;
	};
	
	// register b2　// 1メッシュに一つ
	struct MaterialObjectBuffer {
		DirectX::XMFLOAT4	ambient;
		DirectX::XMFLOAT4	diffuse;
		DirectX::XMFLOAT4	emissive;
		DirectX::XMFLOAT4	bump;
		DirectX::XMFLOAT4	specular;
		DirectX::XMFLOAT4	sub;
		// X float			transparency;
		// Y float			shininess;
		// Z float			reflectivity;

	};

	// register b3　// 世界に多数？
	struct LightObjectBuffer {
		DirectX::XMFLOAT4 way;
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 color;	// colorのwは光の強さに使う
	};

	// register b4 // 世界に一つ(Update内に渡せばいいと思う)
	struct TimeBuffer {
		DirectX::XMFLOAT4 myTime;
		DirectX::XMFLOAT4 myDeltaTime;
	};

	// register b5 // カメラ1つにつき一個 
	struct PostEffectBuffer {
		DirectX::XMFLOAT4 gausse1;
		DirectX::XMFLOAT4 gausse2;

		DirectX::XMFLOAT4 bloojnm1;
		DirectX::XMFLOAT4 bloom2;
		// float bloom;
	};

	struct BoneBuffer {
		DirectX::XMFLOAT4X4 boneMatrix[400];
	};

	// 実数構造体
	WorldObjectBuffer m_worldObject;
	CameraObejctBuffer m_cameraObject;
	MaterialObjectBuffer m_materialObject;
	LightObjectBuffer m_lightObject[LIGHT_MAX]; // 複数ある可能性があるので配列
	TimeBuffer m_time;
	PostEffectBuffer m_postEffect; 
	BoneBuffer m_bone;

	// コンスタントバッファ
	ConstantBuffer m_worldObjectBuffer;
	ConstantBuffer m_cameraObjectBuffer;
	ConstantBuffer m_materialObjectBuffer;
	ConstantBuffer m_lightObjectBuffer;
	ConstantBuffer m_timeBuffer;
	ConstantBuffer m_postEffectBuffer;
	ConstantBuffer m_boneBuffer;

	DeviceContext m_deviceContext;

	static unsigned int m_lightNum;
	unsigned int m_boneNum;
public:
	SubResourceSendManager();
	void Initialize();

	void Update();

	void SetWorldObjectBuffer(const math::Matrix& _world);
	void SetCameraObjectBuffer(
		const math::Matrix& _view,
		const math::Matrix& _projection,
		const math::Matrix& _invers,
		const math::Vector4& _position);
	void SetMaterialBuffer(
		const math::Vector4& _ambient,
		const math::Vector4& _diffuse,
		const math::Vector4& _emissive,
		const math::Vector4& _bump,
		const math::Vector4& _specular,
		const float& _transparency,
		const float& _shininess,
		const float& _reflectivity);
	void SetMaterialBuffer(const std::shared_ptr<render::Material> _material);
	void SetLightBuffer(
		const math::Vector4& _way,
		const math::Vector4& _color);
	void SetTimeBuffer(
		const math::Vector4& _time, 
		const math::Vector4& _deltaTime);
	void SetPostEffect(
		const std::array<float, 8>& _gauss,
		const std::array<float, 8>& _bloomDiffuse,
		const float& _bloomSpecular
	);
	void SetBone(const std::vector<math::Matrix>& _matrix);
};

}	// namespace directx
}	// namespace mslib