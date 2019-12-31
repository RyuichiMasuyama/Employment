#include "./Renderer/RenderTerget.h"
#include "./Renderer/PostEffect.h"
#include "./Windows/WindowsDefineData.h"

#ifdef DIRECTX11
#include "./DirectX/SubResourceSendManager.h"
#include "./DirectX/DirectXRenderTerget.h"
#endif

namespace mslib {
namespace render {

RenderTerget::~RenderTerget() = default;
//
//void RenderTerget::Initalize(RendringSoftRenderTergetPtr _softRenderTerget) {
//	m_softRenderTerget = _softRenderTerget;
//}

RenderTergetManager::RenderTergetManager() {
	CreateRenderTerget(RenderTergetType::BASIC);
}

std::weak_ptr<RenderTerget> RenderTergetManager::CreateRenderTerget(const RenderTergetType _renderType) {
	std::weak_ptr<RenderTerget> ptr;

#ifdef DIRECTX11
	switch (_renderType) {
	case RenderTergetType::BASIC: {
		auto instance = std::make_shared<directx::BasicDirectXRenderTerget>();
		m_renderTergets.push_back(instance);
		m_basic.push_back(instance);
		instance->m_softRenderTerget = instance;
		ptr = instance;
		break;
	}
	case RenderTergetType::MAIN: {
		auto instance = std::make_shared<directx::MainDirectXRenderTerget>();
		m_renderTergets.push_back(instance);
		m_mainCameraRender.push_back(instance);
		instance->m_softRenderTerget = instance;
		ptr = instance;
		break;
	}
	case RenderTergetType::SUBCAMERA: {
		auto instance = std::make_shared<directx::SubDirectXRenderTerget>();
		m_renderTergets.push_back(instance);
		m_subCameraRender.push_back(instance);
		instance->m_softRenderTerget = instance;
		ptr = instance;
		break;
	}
	case RenderTergetType::SHADOW_MAP: {
		auto instance = std::make_shared<directx::ShadowMapDirectXRenderTerget>();
		m_renderTergets.push_back(instance);
		m_shadowMapRender.push_back(instance);
		instance->m_softRenderTerget = instance;
		ptr = instance;
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
	case RenderTergetType::BASIC:
		return m_basic;
		break;
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
	assert(true);
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

void RenderTerget::BufferClear() {
	m_softRenderTerget.lock()->BufferClear();
}

void RenderTerget::RenderBefor() {
#ifdef DIRECTX11
	// カメラの情報をコンスタントバッファに投げる
	directx::SubResourceSendManager::GetInstance().SetCameraObjectBuffer(
		*m_worldMatrix.lock(),
		*m_projectionMatrix .lock(),
		*m_inversMatrix.lock(),
		math::Vector4(*m_position)
	); 
#endif
}

void RenderTerget::DrawPostEffect() {
	if(!m_postEffect.expired()) m_postEffect.lock()->Rendring();
}

render::CameraTexture RenderTerget::GetCameraTexture() {
	return m_softRenderTerget.lock()->GetCameraTexture();
}

std::weak_ptr<math::Matrix> RenderTerget::GetCameraProjection() {
	return m_projectionMatrix;
}

}
}