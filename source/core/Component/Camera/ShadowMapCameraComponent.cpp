
#include "./ShadowMapCameraComponent.h"
#include "./Windows/WindowsDefineData.h"

namespace mslib {
namespace component {
ShadowMapCameraComponent::ShadowMapCameraComponent() {
	// レンダーターゲットを通常のカメラとして設定
	m_renderTerget = render::RenderTergetManager::GetInstance().CreateRenderTerget(render::RenderTergetType::SHADOW_MAP);
}

void ShadowMapCameraComponent::Initialize() {
	base::Initialize();
	// 基本的なプロジェクション行列を設定
	SetProjection(1.0f, 10000.0f, DirectX::XM_PIDIV2, SCREEN_X, SCREEN_Y);
	SetLength(10.f);
}

void ShadowMapCameraComponent::Update() {
	base::Update();
}
}
}
