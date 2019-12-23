#pragma once
#include <Singleton.h>
#include <unordered_map>
#include <any>

#ifdef DIRECTX11
#include "./TextureLoader.h"
#endif // DIRECTX11

// LoaderŠÖŒW‚Ì–¼‘O‹óŠÔ“ˆê‚·‚é‚×‚«‚¾‚Á‚½c
namespace mslib {
namespace loader {
class TextureLoader;
class ShaderLoader;
class MeshLoader;
class MyMesh;
}

namespace assets {

#ifdef DIRECTX11
using AssetBase = directx::D3D11BaseComptr;
#endif

class AssetsManager :public pattern::Singleton<AssetsManager>{
	friend loader::TextureLoader;
	friend loader::ShaderLoader;
	friend loader::MeshLoader;
public:
	void UnLoad(std::string);
private:
	std::unordered_map<std::string, std::any> m_assets;

};

}
}