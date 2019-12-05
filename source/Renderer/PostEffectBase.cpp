#include "./PostEffectBase.h"
namespace mslib {
namespace render {

PostEffectBase::PostEffectBase(CameraTexture _cameraTexture):DirectXPostEffect(_cameraTexture){

}

//void PostEffectBase::SetFlag(bool _flag, POSTEFFECT_TYPE _postEffectType) {
//	switch (_postEffectType) {
//	case POSTEFFECT_TYPE::GAUSS:
//		m_postEffectStatus.OnFlag = _flag;
//		break;
//	case POSTEFFECT_TYPE::BLOOM:
//		m_postEffectStatus.BloomFlag = _flag;
//		break;
//	}
//}
void PostEffectBase::SetStatus(PostEffectStatus _postEffectStatus) {
	m_postEffectStatus = _postEffectStatus;
}
}
}
