#include "./CameraComponent.h"
#include "./Windows/WindowsDefineData.h"

namespace mslib {
namespace component {
CameraComponent::CameraComponent() {
	// レンダーターゲットを通常のカメラとして設定
	m_renderTerget = render::RenderTergetManager::GetInstance().CreateRenderTerget(render::RenderTergetType::MAIN);
}

void CameraComponent::Initialize() {
	base::Initialize();

	// 基本的なプロジェクション行列を設定
	SetProjection(1.0f, 100000.0f, DirectX::XM_PIDIV2, SCREEN_X, SCREEN_Y);
	SetLength(10.f);
}

void CameraComponent::Update() {
	base::Update();
}
}  // namespace component
}  // namespace mslib
