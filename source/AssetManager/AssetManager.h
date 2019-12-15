#pragma once
#include <Singleton.h>
#include <unordered_map>
#include <any>

#ifdef DIRECTX11
#include "./TextureLoader.h"
#endif // DIRECTX11


namespace mslib {
namespace texture {
class TextureLoader;
}
namespace shader {
class ShaderLoader;
}
namespace mesh {
class MeshLoader;
}
namespace render {
class MyMesh;
}

namespace assets {

#ifdef DIRECTX11
using AssetBase = directx::D3D11BaseComptr;
#endif

class AssetsManager :public pattern::Singleton<AssetsManager>{
	friend texture::TextureLoader;
	friend shader::ShaderLoader;
public:
	void UnLoad(std::string);
private:
	std::unordered_map<std::string, std::any> m_assets;

};

class AssetsMeshs :public pattern::Singleton<AssetsMeshs> {
	friend mesh::MeshLoader;
public:
	void UnLoad(std::string);
private:
	std::unordered_map<std::string, std::shared_ptr<render::MyMesh>> m_assets;
};

}
}