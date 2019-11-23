#pragma once

#include "./core/Object/Object.h"
#include "./Renderer/DirectXRenderManager.h"


namespace mslib {
namespace component {

class Render2DComponent :public Component {

public:
	Render2DComponent(const std::string& _drawName) { m_drawName = _drawName; }

	void FixedUpdate()override {
		render::DirectXRender::GetInstance().Draw(m_drawName, m_transform.lock()->m_matrix);
	}


private:
	std::string m_drawName;
};

}
}