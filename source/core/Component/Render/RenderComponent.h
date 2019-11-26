#pragma once

#include "./core/Object/Object.h"
#include "./Renderer/Render.h"

namespace mslib {
namespace render {
class MyMesh;
}

namespace component {

class RenderComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	RenderComponent(std::weak_ptr<render::MyMesh> _mesh) :m_mesh(_mesh) {}

	void FixedUpdate()override;

private:
	std::weak_ptr<render::MyMesh> m_mesh;
};

}
}