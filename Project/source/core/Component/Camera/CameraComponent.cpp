#include "./CameraComponent.h"
#include "./Windows/WindowsDefineData.h"

namespace mslib {
namespace component {

void CameraComponent::Initialize() {
	base::Initialize();

	// �����_�[�^�[�Q�b�g��ʏ�̃J�����Ƃ��Đݒ�
	m_renderTerget = render::RenderTergetManager::GetInstance().CreateRenderTerget(render::RenderTergetType::NORMAL);

	// ��{�I�ȃv���W�F�N�V�����s���ݒ�
	SetProjection(1.0f, 10000.0f, DirectX::XM_PIDIV2, SCREEN_X, SCREEN_Y);
	SetLength(10.f);
}

void CameraComponent::Update() {
	base::Update();
}

}  // namespace component
}  // namespace mslib
