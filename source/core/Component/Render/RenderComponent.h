#pragma once

#include "./core/Object/Object.h"
#include "./Renderer/DirectXRenderManager.h"

namespace mslib {
namespace component {

class RenderComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	RenderComponent(const std::string& _drawName) { m_drawName = _drawName; }

	void FixedUpdate()override {
		static math::Vector3 angle = { -90,0,0.f };
		static math::Vector3 pos = { 0.f,-3.f,0.f };
		static math::Vector3 size = { 0.3f,0.3f,0.3f };
		static bool flag = true;

		static math::Quaternion rot;
		static math::Quaternion addRot;
		math::Matrix mat;

		mat.Scaling(size);
		if (flag) {
			rot.Rotate(math::Vector3(-90.f, 0.f, 0.f));
			flag = false;
		}
		addRot.Rotate(math::Vector3(0.f,1.f, 0.f));
		rot *= addRot;
		mat *= rot.GetMatrix();
		mat.MovePosition(pos);

	//	MyDirectX11::Render::DirectXRender::GetInstance().Draw(m_drawName, mat);

		render::DirectXRender::GetInstance().Draw(m_drawName, m_transform.lock()->m_matrix);
	}


private:
	std::string m_drawName;
};

}
}