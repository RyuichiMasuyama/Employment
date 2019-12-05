#pragma once

#include "./DirectXPostEffect.h"

namespace mslib {
namespace render{
class PostEffectBase;

// �\�ɏo�Ȃ��ADirectX��OpenGL���p��
// �����_�����O�ɕK�v�ȏ���n�����p�N���X
class PostEffectBase : public directx::DirectXPostEffect {
public:
	PostEffectBase(CameraTexture _cameraTexture);
	~PostEffectBase() = default;

	void SetStatus(PostEffectStatus _postEffectStatus);
private:

};

}
}