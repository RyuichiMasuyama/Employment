#include "ModelLoader.h"
#include "./Renderer/Model.h"

namespace mslib {
namespace loader {
std::shared_ptr<render::ModelData> ModelLoader::Load(std::string _fileName) {
	auto& assets = assets::AssetsManager::GetInstance().m_assets[_fileName];

	// •Û‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©Šm”F
	if (assets.has_value()) {
		auto returnObj = std::any_cast<std::shared_ptr<render::ModelData>>(assets);
		return returnObj;
	}
	auto newModelData = std::make_shared<render::ModelData>();

	newModelData->Load(_fileName);
	
	assets::AssetsManager::GetInstance().m_assets[_fileName] = newModelData;

	return newModelData;

	// assets = data;
}

}
}
