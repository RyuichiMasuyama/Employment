#include "./Render.h"

#include <algorithm>
#include <functional>

#ifdef DIRECTX11
#include "./DirectX/DirectXPipeline.h"
#include "../DirectX/SubResourceSendManager.h"
#endif

#include "RenderTerget.h"

namespace mslib {
namespace render {

void Render::Draw( math::Matrix& _mat,  Pipeline* _pipelineFunction) {
	// RenderObjectCommand command(_mat, std::bind(&Pipeline::Draw, _pipelineFunction));
	RenderObjectCommand command(_mat, _pipelineFunction);
	m_commandDynamicArray.push_back(command);
}

// 1�D���ׂẴJ�������Y��ɂ���
// 2�D�V���h�E�}�b�v��`�悷��
// 3�D�T�u�J������`�悷��
// 4�D�V���h�E�}�b�v�ƃT�u�J�����̃T���v���[��ResourceView���Z�b�g����
// 5�D���C���J������`�悷��
// 6�D���C���J�����̃��\�[�X�r���[���Z�b�g����
// 7�D�|�X�g�G�t�F�N�g��������
void Render::Rendering() {
	auto& rendeRtergets = RenderTergetManager::GetInstance().GetRenderTergets();

	auto& basic= RenderTergetManager::GetInstance().GetRenderTergets(RenderTergetType::BASIC);
	auto& shadeowMap = RenderTergetManager::GetInstance().GetRenderTergets(RenderTergetType::SHADOW_MAP);
	auto& main = RenderTergetManager::GetInstance().GetRenderTergets(RenderTergetType::MAIN);
	auto& sub = RenderTergetManager::GetInstance().GetRenderTergets(RenderTergetType::SUBCAMERA);

	// ���C�g���M
	directx::SubResourceSendManager::GetInstance().Update();

	// �S�J�����̃o�b�t�@���N���A����
	for (auto itr : rendeRtergets) {
		/*itr->BufferClear();*/
	}

	// �V���h�E�}�b�v
	for (auto& itr : shadeowMap) {
		itr.lock()->BufferClear();
		itr.lock()->RenderBefor();
		for (auto pipe : m_commandDynamicArray) {
			directx::SubResourceSendManager::GetInstance().SetWorldObjectBuffer(pipe.m_mat);
			// pipe.m_function();
			pipe.m_pipelinePtr->NoSetShaderDraw();
		}
	}

	// �T�u�J����
	for (auto& itr : sub) {
		itr.lock()->BufferClear();
		itr.lock()->RenderBefor();
		for (auto pipe : m_commandDynamicArray) {
			directx::SubResourceSendManager::GetInstance().SetWorldObjectBuffer(pipe.m_mat);
			// pipe.m_function();
			pipe.m_pipelinePtr->Draw();
		}
		itr.lock()->DrawPostEffect();
	}

	// ���C���J����
	for (auto& itr : main) {
		itr.lock()->BufferClear();
		itr.lock()->RenderBefor();
		for (auto pipe : m_commandDynamicArray) {
			directx::SubResourceSendManager::GetInstance().SetWorldObjectBuffer(pipe.m_mat);
			// pipe.m_function();
			pipe.m_pipelinePtr->Draw();
		}
		itr.lock()->DrawPostEffect();
	}

	basic[0].lock()->BufferClear();
	m_rendering->GetPipeline()->SetTexture(main[0].lock()->GetCameraTexture(), 0);
	m_rendering->GetPipeline()->Draw();

	m_commandDynamicArray.clear();
}

void Render::ImGuiCare() {
#ifdef DIRECTX11
	auto context = directx::DirectX11Manager::GetInstance().GetDeviceContext();
	context->GSSetShader(nullptr, nullptr, 0);
	context->HSSetShader(nullptr, nullptr, 0);
	context->DSSetShader(nullptr, nullptr, 0);
#endif
}

}
}