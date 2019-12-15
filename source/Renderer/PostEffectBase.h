#pragma once

#include "./DirectXPostEffect.h"

namespace mslib {
namespace render{
class PostEffectBase;

// 表に出ない、DirectXかOpenGLを継承
// レンダリングに必要な情報を渡す中継クラス
class PostEffectBase : public directx::DirectXPostEffect {
public:
	PostEffectBase(CameraTexture _cameraTexture);
	~PostEffectBase() = default;

	void SetStatus(PostEffectStatus _postEffectStatus);
private:

};

}
}