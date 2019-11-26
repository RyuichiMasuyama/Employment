#include "./DepseBufferRender2DGameObject.h"
#include "./core/Component/Render/Render2DComponent.h"
#include "./AssetManager/MeshLoader.h"

#include <ImGui/imgui.h>

namespace mslib {
namespace origin {
void DepseBuffer2DRenderGameObject::Initialize()
{
	base::Initialize();

	CreateUpdateFunction(TestUpdateName, &DepseBuffer2DRenderGameObject::TestUpdate, this);
	SetUpdateFunction(TestUpdateName);
	mesh::MeshLoader loader;
	AddComponent<component::Render2DComponent>(loader.Load("polygon.obj"));
}
void DepseBuffer2DRenderGameObject::ImGuiDraw()
{
	ImGui::Text("DepseRender");
	
	ImGui::SliderFloat3("DepseRender:Position", m_position.GetPtr(), -2.f, 2.f);
	ImGui::SliderFloat3("DepseRender:Scale", m_scale.GetPtr(), 0.1f, 1.f);

	m_matrix.Scaling(m_scale);
	m_matrix.MovePosition(m_position);
}
void DepseBuffer2DRenderGameObject::TestUpdate()
{
}

}
}
