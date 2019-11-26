#pragma once

#include "./DirectX/DirectX11Manager.h"
#include <unordered_map>

namespace mslib {
namespace texture {

#ifdef DIRECTX11
using Texture = Microsoft::WRL::WeakRef;
#endif

class TextureLoader {
public:
	TextureLoader() = default;

	Texture Load(std::string _fileName);

private:
	//bool CrateTexture();
};

}
}