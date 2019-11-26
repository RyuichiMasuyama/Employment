#pragma once

#include "./core/Object/Object.h"
#include "./Renderer/Render.h"

// ���݂͂��ׂ�3D��vertex���g�p����2D���Č����Ă��邪
// ����A2D��vertex���쐬���đΉ����������Ȃ̂�
// �ꉞ�ARender2DComponent�𐶐����Ă����B2D�ɂ�����̂�
// ���̃R���|�[�l���g��ʂ��ă����_�����O���邱��

namespace mslib {
namespace render {
class MyMesh;
}
namespace component {

class Render2DComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	Render2DComponent(std::weak_ptr<render::MyMesh> _mesh) { m_mesh = _mesh; }

	void FixedUpdate()override;


private:
	std::weak_ptr<render::MyMesh> m_mesh;
};

}
}