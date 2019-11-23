#pragma once

#include "./DirectX/DirectX11Manager.h"
#include "./DirectX/DeviceGetter.h"
#include "./Singleton.h"
#include "./MyDirectXMath.h"
#include <memory>
#include <vector>

namespace mslib {
namespace render {
class DirectXRender;
}
}

namespace mslib {
namespace render {

enum class RenderTergetType{
	NORMAL,
	SUBCAMERA,
	SHADOW_MAP,
	MAX
};

// �����_�[�^�[�Q�b�g����
// �����̌����Ă��ƁA�����_�[�^�[�Q�b�g1��
// �J����1�̏�ԂɂȂ�
class RenderTerget :public directx::DeviceContextGetter {
	friend class RenderTergetManager;
public:
	RenderTerget() { m_inceNum++; };
	~RenderTerget() = default;

	void SetRenderTerget();
	void SetShaderResorce(int _number);
	mslib::directx::RenderTargetView GetRenderTergetView() { return m_renderTergetView; };

	void SetCameraData(
		std::weak_ptr<math::Matrix> _worldMatrix,
		std::weak_ptr<math::Matrix> _projectionMatrix,
		std::weak_ptr<math::Matrix> _inversMatrix,
		math::Vector3* _position);

protected:
	mslib::directx::RenderTargetView m_renderTergetView;
	mslib::directx::SamplerState m_samplerState;
	mslib::directx::ShaderTexture m_shaderResourceView;
	mslib::directx::Texture2D m_texture2d;

private:
	unsigned int m_inceNum;

	// �J�����̏���ێ�
	// �J�����̍s��
	std::weak_ptr<math::Matrix> m_worldMatrix;

	// �J�����̃v���W�F�N�V�����s��
	std::weak_ptr<math::Matrix> m_projectionMatrix;

	// �J�����̋t�s��
	std::weak_ptr<math::Matrix> m_inversMatrix;

	// �ʒu���
	math::Vector3 *m_position;
};

class SubCameraRender :public RenderTerget, directx::DeviceGetter {
public:
	SubCameraRender();
	~SubCameraRender() = default;
};

class ShadowMapRender :public RenderTerget, directx::DeviceGetter {
public:
	ShadowMapRender();
	~ShadowMapRender() = default;
};

class RenderTergetManager :public pattern::Singleton<RenderTergetManager> {
public:
	std::weak_ptr<RenderTerget> CreateRenderTerget(const RenderTergetType _renderType);
	const std::vector<std::shared_ptr<RenderTerget>>& GetRenderTergets() { return m_renderTergets; }

	// �����_�[�^�[�Q�b�g��n���Ə�������
	void ElaseRenderTerget(std::weak_ptr<RenderTerget> _renderTerget);

private:
	std::vector<std::shared_ptr<RenderTerget>> m_renderTergets;
};

}
}
