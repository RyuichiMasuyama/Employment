#pragma once

#include "./DirectX/DirectX11Manager.h"
#include <unordered_map>

namespace mslib {
namespace texture {

#ifdef DIRECTX11
using Texture = directx::ShaderTexture;
#endif
}
namespace loader {
class TextureLoader {
public:
	TextureLoader() = default;

	texture::Texture Load(std::string _fileName);

private:
	//bool CrateTexture();
};

}
}