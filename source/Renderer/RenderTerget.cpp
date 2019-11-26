#include "./Renderer/RenderTerget.h"
#include "./Renderer/PostEffect.h"
#include "./Windows/WindowsDefineData.h"
#include "./DirectX/SubResourceSendManager.h"
#include "./DirectX/DirectXRenderTerget.h"

namespace mslib {
namespace render {

RenderTerget::~RenderTerget() = default;

void RenderTerget::Initalize(RendringSoftRenderTergetPtr _softRenderTerget) {
	m_softRenderTerget = _softRenderTerget;
}

std::weak_ptr<RenderTerget> RenderTergetManager::CreateRenderTerget(const RenderTergetType _renderType) {
	std::weak_ptr<RenderTerget> ptr;

#ifdef DIRECTX11
	switch (_renderType) {
	case RenderTergetType::MAIN: {
		auto instance = std::make_shared<directx::MainDirectXRenderTerget>(RenderTergetType::MAIN);
		m_renderTergets.push_back(instance);
		ptr.lock()->m_softRenderTerget = instance;
		break;
	}
	case RenderTergetType::SUBCAMERA: {
		auto instance = std::make_shared<directx::SubDirectXRenderTerget>(RenderTergetType::SUBCAMERA);
		m_renderTergets.push_back(instance);
		ptr.lock()->m_softRenderTerget = instance;
		break;
	}
	case RenderTergetType::SHADOW_MAP: {
		auto instance = std::make_shared<directx::ShadowMapDirectXRenderTerget>(RenderTergetType::SHADOW_MAP);
		m_renderTergets.push_back(instance);
		ptr.lock()->m_softRenderTerget = instance;
		break;
	}
	default:
		break;
	}
#endif // !DIRECTX11

	return ptr;
}

const std::vector<std::weak_ptr<RenderTerget>>& RenderTergetManager::GetRenderTergets(const RenderTergetType _renderType) {
	switch (_renderType)
	{
	case RenderTergetType::MAIN:
		return m_mainCameraRender;
		break;

	case RenderTergetType::SUBCAMERA:
		return m_subCameraRender;
		break;

	case RenderTergetType::SHADOW_MAP:
		return m_shadowMapRender;

	default:
		break;
	}
}

void RenderTergetManager::ElaseRenderTerget(std::weak_ptr<RenderTerget> _renderTerget) {
	for (auto itr = m_renderTergets.begin(); itr != m_renderTergets.end(); itr++) {
		if ((*itr)->m_inceNum == _renderTerget.lock()->m_inceNum) {
			m_renderTergets.erase(itr);
		}
	}
}

void RenderTerget::SetRenderTerget() {
}

void RenderTerget::SetShaderResorce(int _number) {
	m_softRenderTerget.lock()->SetRenderTerget();

	directx::SubResourceSendManager::GetInstance().SetCameraObjectBuffer(
		*m_worldMatrix.lock(),
		*m_projectionMatrix.lock(),
		*m_inversMatrix.lock(),
		*m_position
	);
}

void RenderTerget::SetCameraData(
	std::weak_ptr<math::Matrix> _worldMatrix,
	std::weak_ptr<math::Matrix> _projectionMatrix,
	std::weak_ptr<math::Matrix> _inversMatrix,
	math::Vector3* _position) {
	m_worldMatrix = _worldMatrix;
	m_projectionMatrix = _projectionMatrix;
	m_inversMatrix = _inversMatrix;
	m_position = _position;
}

void RenderTerget::SetPostEffectData(std::weak_ptr<PostEffect> _postEffect) {
	m_postEffect = _postEffect;
}

}
}