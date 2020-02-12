#include "AtariGameObject.h"
#include <./core/CollisionManager.h>
#include <./ImGui/imgui.h>
#include <./core/FpsManager.h>

namespace mslib {
namespace object {

render::ModelData AtariGameObject::m_baseModel;

// マテリアルデータ
render::MaterialData AtariGameObject::m_materialDataHit;
render::MaterialData AtariGameObject::m_materialDataNoHit;

bool AtariGameObject::once = false;

void AtariGameObject::Initialize() {
	base::Initialize();

	CreateUpdateFunction(TestUpdateName, &AtariGameObject::AtariUpdate,this);
	SetUpdateFunction(TestUpdateName);

	if (!once) {
		// モデルロード
		/*m_baseModel.Load("assets/SphereAtari.fbx");
		m_baseModel.SetPixelShader("shader/ps.fx");
		m_baseModel.SetVertexShader("shader/testvs.fx");*/

		// マテリアル当たった時
		m_materialDataHit.ambient.x = 1.f;
		m_materialDataHit.ambient.y = 0.f;
		m_materialDataHit.ambient.z = 0.f;

		// マテリアル当らなかった時
		m_materialDataNoHit.ambient.x = 0.f;
		m_materialDataNoHit.ambient.y = 1.f;
		m_materialDataNoHit.ambient.z = 0.f;

		once = true;
	}

	//loader::ModelLoader modelLoader;
	//auto modelPtr= modelLoader.Load("assets/SphereAtari.fbx");
	//modelPtr->SetPixelShader("shader/ps.fx");
	//modelPtr->SetVertexShader("shader/testvs.fx");
	//modelPtr->SetMaterial(m_materialDataHit, 0);

	m_modelData.Load("assets/SphereAtari.fbx");
	m_modelData.SetPixelShader("shader/ps.fx");
	m_modelData.SetVertexShader("shader/testvs.fx");
	m_modelData.SetMaterial(m_materialDataNoHit, 0);
	
	// 追加Component
	AddComponent<component::ModelRenderComponent>(&m_modelData);
	m_colSphCom = AddComponent<component::CollisionSphereComponent>();
	AddComponent<component::AtariComponent>(m_materialDataHit, m_materialDataNoHit, m_modelData);
	 
	// ランダムの幅
	int randomWight = 1000;
	// floatの精度
	int precision = 100;

	float sizeRandomWight = 10;

	float sizeRandom = static_cast<float>(Random(1 * precision, sizeRandomWight*precision))/ precision;

	m_colSphCom.lock()->SetSize(sizeRandom);
	m_scale = math::Vector3(sizeRandom, sizeRandom, sizeRandom);

	// ランダムの値を取得
	math::Vector3 random = math::Vector3(
		static_cast<float>(Random(-randomWight* precision, randomWight* precision)),
		static_cast<float>(Random(-randomWight * precision, randomWight* precision)),
		static_cast<float>(Random(-randomWight * precision, randomWight* precision)));

	// 位置を代入
	// m_position = random / precision;
	m_position = (COLLISION_THREE_SIZE_MAX + COLLISION_THREE_SIZE_MIN) / 2;

	// 方向ベクトルのランダムの幅

	int randRotWight = 1;

	// ランダムの値を取得
	random = math::Vector3(
		static_cast<float>(Random(-randRotWight * precision, randRotWight* precision)),
		static_cast<float>(Random(-randRotWight * precision, randRotWight* precision)),
		static_cast<float>(Random(-randRotWight * precision, randRotWight* precision)));

	// 正規化した方向ベクトルを代入
	m_moveLook = random.GetNormal();

	m_speed = static_cast<float>(Random(10 * precision, 100 * precision));
	m_speed /= precision;

}

void AtariGameObject::ImGuiDraw() {
}

void AtariGameObject::AtariUpdate() {

	auto time = FpsManager::GetInstance().GetDeltaTime();

	// 位置更新
	m_position += m_moveLook * m_speed * time;

	auto threeMin = COLLISION_THREE_SIZE_MIN;
	auto threeMax = COLLISION_THREE_SIZE_MAX;

	auto aabb = m_colSphCom.lock()->GetAABB();
	// 範囲外ならベクトルを逆に
	// 最初
	if (m_position.x - m_scale.x < threeMin.x || threeMax.x < m_position.x + m_scale.x) {
		m_position -= m_moveLook * m_speed * time;
		m_moveLook.x = -m_moveLook.x;
	}
	if (m_position.y - m_scale.y < threeMin.y || threeMax.y < m_position.y + m_scale.y) {
		m_position -= m_moveLook * m_speed * time;
		m_moveLook.y = -m_moveLook.y;
	}
	if (m_position.z - m_scale.z < threeMin.z || threeMax.z < m_position.z + m_scale.z) {
		m_position -= m_moveLook * m_speed * time;
		m_moveLook.z = -m_moveLook.z;
	}
}

}
namespace component {
void AtariComponent::Initialize() {
	base::Initialize();
	m_hitFlag = false;
}

void AtariComponent::Update() {
}

void AtariComponent::FixedUpdate() {
	if (m_hitFlag) {
		m_baseModel.SetMaterial(m_materialDataHit, 0);
	}
	else {
		m_baseModel.SetMaterial(m_materialDataNoHit, 0);
	}
	m_hitFlag = false;
}


void AtariComponent::HitTriggerStay() {
	m_hitFlag = true;
}

}
}

