#include "./Field.h"
#include <./core/Component/Render/ModelRenderComponent.h>

namespace mslib {
namespace object {

void FieldGameObject::Initialize() {
	base::Initialize();

	m_modelData.Load("assets/Ground.fbx");
	m_modelData.SetVertexShader("shader/testvs.fx");
	m_modelData.SetPixelShader("shader/ps2d.fx");
	m_modelData.SetTexture("terrain_far_01_a2_result_result.jpg",0);

	AddComponent<component::ModelRenderComponent>(&m_modelData);
	m_position.z -=500.f;
}

}
}