#include "./CameraComponent.h"
#include "./Windows/WindowsDefineData.h"

namespace mslib {
namespace component {
CameraComponent::CameraComponent() {
	// �����_�[�^�[�Q�b�g��ʏ�̃J�����Ƃ��Đݒ�
	m_renderTerget = render::RenderTergetManager::GetInstance().CreateRenderTerget(render::RenderTergetType::MAIN);
}

void CameraComponent::Initialize() {
	base::Initialize();

	// ��{�I�ȃv���W�F�N�V�����s���ݒ�
	SetProjection(0.1f, 10000.0f, DirectX::XM_PIDIV2/2, SCREEN_X, SCREEN_Y);
	SetLength(10.f);
}

void CameraComponent::Update() {
	base::Update();
}
}  // namespace component
}  // namespace mslib
