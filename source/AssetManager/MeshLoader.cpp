#include "./MeshLoader.h"
#include "./AssetManager.h"
#include "./MeshPrimitive.h"

namespace mslib {
namespace mesh {
MeshLoader::MeshLoader() {
	assets::AssetsMeshs::GetInstance().m_assets["Quad"] = std::make_shared<Primitive::QuadPrimitive>();
}

std::shared_ptr<render::MyMesh> MeshLoader::Load(std::string _fileName){
	auto& asset = assets::AssetsMeshs::GetInstance().m_assets[_fileName];
	// ’†g‚ª‚È‚¯‚ê‚Î¶¬‚·‚é
	if (asset.use_count() != 0) {
		return asset;
	}

	// ¶¬‚Æƒ[ƒh
	asset = std::make_shared<render::MyMesh>();
	asset->Load(_fileName);

	return asset;
}
}
}
