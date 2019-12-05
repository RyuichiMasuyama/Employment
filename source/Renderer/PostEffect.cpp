#include "./PostEffect.h"
namespace mslib {
namespace render {
void PostEffect::Rendring() {
	m_postEffect.Rendering();
}
void PostEffect::SetStatus(PostEffectStatus _status) {
	m_postEffect.SetStatus(_status);
}
}
}
