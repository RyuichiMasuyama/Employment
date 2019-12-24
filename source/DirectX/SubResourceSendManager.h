#pragma once

#include "./MyDirectXMath.h"
#include "./DirectX/DirectX11Manager.h"
#include "./Renderer/RenderObject.h"
#include <Singleton.h>
#include <array>

// ������i�K���b�s���O��������
// ���b�s���O������Ɠ�����Singleton�̉�����
// ���Ԃ�static�ɂȂ�Ɨ\�z�����

namespace mslib {
namespace directx{
class SubResourceSendManager :public pattern::Singleton<SubResourceSendManager> {
public:
	static constexpr int LIGHT_MAX = 100;
private:	
	// register b0	// 1�I�u�W�F�N�g�Ɉ��
	struct WorldObjectBuffer {
		DirectX::XMMATRIX world;
	};

	// register b1�@// �J���������_�[�^�[�Q�b�g�Ɉ��
	struct CameraObejctBuffer {
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		DirectX::XMMATRIX invers;
		DirectX::XMFLOAT4 position;
		DirectX::XMMATRIX shadow;
	};
	
	// register b2�@// 1���b�V���Ɉ��
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

	// register b3�@// ���E�ɑ����H
	struct LightObjectBuffer {
		DirectX::XMFLOAT4 way;
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 color;	// color��w�͌��̋����Ɏg��
	};

	// register b4 // ���E�Ɉ��(Update���ɓn���΂����Ǝv��)
	struct TimeBuffer {
		DirectX::XMFLOAT4 myTime;
		DirectX::XMFLOAT4 myDeltaTime;
	};

	// register b5 // �J����1�ɂ���� 
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

	// �����\����
	WorldObjectBuffer m_worldObject;
	CameraObejctBuffer m_cameraObject;
	MaterialObjectBuffer m_materialObject;
	LightObjectBuffer m_lightObject[LIGHT_MAX]; // ��������\��������̂Ŕz��
	TimeBuffer m_time;
	PostEffectBuffer m_postEffect; 
	BoneBuffer m_bone;

	// �R���X�^���g�o�b�t�@
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