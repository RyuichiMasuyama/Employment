#include "./MeshLoader.h"
#include "./AssetManager.h"

namespace mslib {
namespace mesh {
std::weak_ptr<render::MyMesh> MeshLoader::Load(std::string _fileName){
	auto& asset = assets::AssetsMeshs::GetInstance().m_assets[_fileName];
	// 中身がなければ生成する
	if (asset.use_count() != 0) {
		return asset;
	}

	// 生成とロード
	asset = std::make_shared<render::MyMesh>();
	asset->Load(_fileName);

	return asset;
}
}
}
