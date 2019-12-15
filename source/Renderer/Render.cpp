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

// 1．すべてのカメラを綺麗にする
// 2．シャドウマップを描画する
// 3．サブカメラを描画する
// 4．シャドウマップとサブカメラのサンプラーとResourceViewをセットする
// 5．メインカメラを描画する
// 6．メインカメラのリソースビューをセットする
// 7．ポストエフェクトをかける
void Render::Rendering() {
	auto& rendeRtergets = RenderTergetManager::GetInstance().GetRenderTergets();

	auto& basic= RenderTergetManager::GetInstance().GetRenderTergets(RenderTergetType::BASIC);
	auto& shadeowMap = RenderTergetManager::GetInstance().GetRenderTergets(RenderTergetType::SHADOW_MAP);
	auto& main = RenderTergetManager::GetInstance().GetRenderTergets(RenderTergetType::MAIN);
	auto& sub = RenderTergetManager::GetInstance().GetRenderTergets(RenderTergetType::SUBCAMERA);

	// ライト送信
	directx::SubResourceSendManager::GetInstance().Update();

	// 全カメラのバッファをクリアする
	for (auto itr : rendeRtergets) {
		/*itr->BufferClear();*/
	}

	// シャドウマップ
	for (auto& itr : shadeowMap) {
		itr.lock()->BufferClear();
		itr.lock()->RenderBefor();
		for (auto pipe : m_commandDynamicArray) {
			directx::SubResourceSendManager::GetInstance().SetWorldObjectBuffer(pipe.m_mat);
			// pipe.m_function();
			pipe.m_pipelinePtr->NoSetShaderDraw();
		}
	}

	// サブカメラ
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

	// メインカメラ
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