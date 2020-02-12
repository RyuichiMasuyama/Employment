#include "./AssimpLoader.h"
#include "AssetManager.h"

namespace mslib {
namespace loader {

std::shared_ptr<assimp::AssimpScene> AssimpLoader::Load(std::string _materialName) {
	auto& asset = assets::AssetsManager::GetInstance().m_assets[_materialName];
	if (asset.has_value()) {
		auto getAsset = std::any_cast<std::shared_ptr<assimp::AssimpScene>>(asset);
		return getAsset;
	}
	auto newAsset = std::make_shared<assimp::AssimpScene>();

	newAsset->Init(_materialName);
	
	asset = newAsset;
	
	return newAsset;
}

}
}