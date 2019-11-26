#pragma once

#include "./Singleton.h"
#include "./MyDirectXMath.h"
#include <memory>
#include <vector>

#ifdef DIRECTX11
//#include "./DirectX/DirectXRenderTerget.h"
#endif


namespace mslib {

#ifdef DIRECTX11
namespace directx {
class DirectXRenderTerget;
}
#endif

namespace render {

#ifdef DIRECTX11
using RendringSoftRenderTergetPtr = std::weak_ptr< directx::DirectXRenderTerget >;
#endif

struct PostEffect;

enum class RenderTergetType :unsigned int{
	MAIN,
	SUBCAMERA,
	SHADOW_MAP,
	MAX
};

// �����_�[�^�[�Q�b�g����
// �����̌����Ă��ƁA�����_�[�^�[�Q�b�g1��
// �J����1�̏�ԂɂȂ�
class RenderTerget {
	friend class RenderTergetManager;
public:
	RenderTerget(RenderTergetType _renderTergetType) :m_renderTergetType(_renderTergetType) {
		static unsigned int inc = 0;
		m_inceNum = inc;
		inc++;
	};
	~RenderTerget();	// unique_ptr�g�p�̂��ߔ�C�����C����

	void Initalize(RendringSoftRenderTergetPtr _softRenderTerget);

	void SetRenderTerget();
	void SetShaderResorce(int _number);
	// mslib::directx::RenderTargetView GetRenderTergetView() { return m_renderTergetView; };

	void SetCameraData(
		std::weak_ptr<math::Matrix> _worldMatrix,
		std::weak_ptr<math::Matrix> _projectionMatrix,
		std::weak_ptr<math::Matrix> _inversMatrix,
		math::Vector3* _position);

	void SetPostEffectData(std::weak_ptr<PostEffect> _postEffect);

	void Pipeline();

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
	// RT(1)--(1)Camera�̊֌W�Ȃ̂Ő��|��OK
	math::Vector3 *m_position;

	// �|�X�g�G�t�F�N�g�̃f�[�^�[
	// RT(1)--(0?1)PostEffec�Ȃ̂�
	// �ێ����m�F
	std::weak_ptr<PostEffect> m_postEffect;

	RenderTergetType m_renderTergetType; 

	RendringSoftRenderTergetPtr m_softRenderTerget;
};

class RenderTergetManager :public pattern::Singleton<RenderTergetManager> {
public:
	std::weak_ptr<RenderTerget> CreateRenderTerget(const RenderTergetType _renderType);
	const std::vector<std::shared_ptr<RenderTerget>>& GetRenderTergets() { return m_renderTergets; }
	const std::vector < std::weak_ptr<RenderTerget>>& GetRenderTergets(const RenderTergetType _renderType);
	// �����_�[�^�[�Q�b�g��n���Ə�������
	void ElaseRenderTerget(std::weak_ptr<RenderTerget> _renderTerget);

private:
	std::vector<std::shared_ptr<RenderTerget>> m_renderTergets;

	// �J�����̃^�C�v���ς������ǉ�
	std::vector<std::weak_ptr<RenderTerget>> m_shadowMapRender;
	std::vector<std::weak_ptr<RenderTerget>> m_subCameraRender;
	std::vector<std::weak_ptr<RenderTerget>> m_mainCameraRender;
};

}
}