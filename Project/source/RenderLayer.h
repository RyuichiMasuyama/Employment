#pragma once

namespace mslib {
namespace render {

// layer
// •¡»‰Â”\
// ƒJƒƒ‰‚ªlayer‚ğ‚Â
// Object•`‰æ
//	  «
//  2D•`‰æ
//	  «
// PostEffect•`‰æ
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