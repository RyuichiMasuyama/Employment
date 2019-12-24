#pragma once
#include <Singleton.h>
#include <unordered_map>
#include <any>

#ifdef DIRECTX11
#include "./TextureLoader.h"
#endif // DIRECTX11

// Loader関係の名前空間統一するべきだった…
namespace mslib {
namespace loader {
class TextureLoader;
class ShaderLoader;
class MeshLoader;
class MyMesh;
class ModelLoader;
}

namespace assets {

#ifdef DIRECTX11
using AssetBase = directx::D3D11BaseComptr;
#endif

class AssetsManager :public pattern::Singleton<AssetsManager>{
	friend loader::TextureLoader;
	friend loader::ShaderLoader;
	friend loader::MeshLoader;
	friend loader::ModelLoader;
public:
	void UnLoad(std::string);
private:
	std::unordered_map<std::string, std::any> m_assets;

};

}
}