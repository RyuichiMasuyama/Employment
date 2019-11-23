#include "TestGameObject.h"
#include "./core/Component/Render/RenderComponent.h"

#include <ImGui/imgui.h>

namespace mslib {
namespace origin {

struct PostEffectGause {
	math::Vector4 wight1;
	math::Vector4 wight2;
};

void TestGameObject::Initialize() {
	base::Initialize();

	CreateUpdateFunction(TestUpdateName, &TestGameObject::TestUpdate, this);
	SetUpdateFunction(TestUpdateName);

	AddComponent<component::RenderComponent>("dragon");

	directx::BufferCreater creater(directx::DirectX11Manager::GetInstance().GetDevice());

	buff = creater.CreateConstantBuffer(sizeof(PostEffectGause));
}

void TestGameObject::ImGuiDraw() {
	static auto rot = math::Vector3();
	ImGui::SliderFloat3("Position", m_position.GetPtr(), -100.f, 100.f);
	ImGui::SliderFloat3("Roteta", rot.GetPtr(), -360.f, 360.f);
	ImGui::SliderFloat3("Scale", m_scale.GetPtr(), 0.1f, 10.f);
	ImGui::SliderFloat("Gauss", &gauuse, 0.f, 1.f);
	math::Quaternion qu;
	qu.Rotate(rot);
	m_matrix.Scaling(m_scale);
	m_matrix *= qu.GetMatrix();
	m_matrix.MovePosition(m_position);
}
void TestGameObject::TestUpdate() {
	directx::DirectX11Manager::GetInstance().GetDeviceContext();
	float total = 0.0f;
	const int NUM_WEIGHT = 8;
	float mWeights[8];
	//for (int i = 0; i<NUM_WEIGHT; ++i) {
	//	float pos = 1.0f + 2.0f * (float)i;
	//	mWeights[i] = expf(-0.5f * (pos * pos) / gauuse);
	//	total += 2.0f * mWeights[i];
	//}

	//float invTotal = 1.0f / total;
	//for (int i = 0; i<NUM_WEIGHT; ++i) { mWeights[i] *= invTotal; }


	PostEffectGause gause;

	//gause.wight1 = math::Vector4(mWeights[0], mWeights[1], mWeights[2], mWeights[3]);
	//gause.wight2 = math::Vector4(mWeights[4], mWeights[5], mWeights[6], mWeights[7]);

	// ガウス関数による重みの計算
	for (int i = 0; i<NUM_WEIGHT; i++)
	{
		float pos = (float)i * 2.0f;
		mWeights[i] = expf(-pos * pos * gauuse);
		total += mWeights[i];
	}

	// 重みの規格化
	for (int i = 0; i<NUM_WEIGHT; i++)
		mWeights[i] = mWeights[i] / total * 0.5f;

	gause.wight1 = math::Vector4(mWeights[0], mWeights[1], mWeights[2], mWeights[3]);
	gause.wight2 = math::Vector4(mWeights[4], mWeights[5], mWeights[6], mWeights[7]);

	directx::DirectX11Manager::GetInstance().GetDeviceContext()->UpdateSubresource(buff.Get(),
		0,
		nullptr,
		&gause,
		0, 0);

	//コンスタントバッファ4をｂ6レジスタへセット（頂点シェーダー用）
	// directx::DirectX11Manager::GetInstance().GetDeviceContext()->VSSetConstantBuffers(7, 1, buff.GetAddressOf());
	//コンスタントバッファ4をｂ6レジスタへセット(ピクセルシェーダー用)
	directx::DirectX11Manager::GetInstance().GetDeviceContext()->PSSetConstantBuffers(7, 1, buff.GetAddressOf());
}

}
}
