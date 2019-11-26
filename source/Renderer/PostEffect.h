#pragma once

namespace mslib {
namespace render {

struct PostEffect {
	bool GaussFlag;
	float GaussPower;
	
	bool BloomFlag;
	float BloomPower;
};

//class PostEffectCommand {
//
//private:
//	const PostEffect& m_postEffect;
//
//};

}
}