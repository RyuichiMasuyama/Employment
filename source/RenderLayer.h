#pragma once

namespace mslib {
namespace render {

// layer
// �����\
// �J������layer������
// Object�`��
//	  ��
//  2D�`��
//	  ��
// PostEffect�`��
class RenderLayer {

private:
	void Render3D();
	void Render2D();
	void RenderPostEffect();
public:
	// ObjectCommand?
};

}
}