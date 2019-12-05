#pragma once
#include "./PostEffectBase.h"

namespace mslib {
namespace render {
class PostEffect;

class PostEffect {
public:
	PostEffect(CameraTexture _cameraTexture):m_postEffect(_cameraTexture) {};
	~PostEffect() = default;
	
	void Rendring();
	void SetStatus(PostEffectStatus _status);
private:
	PostEffectBase m_postEffect;
};

}
}
