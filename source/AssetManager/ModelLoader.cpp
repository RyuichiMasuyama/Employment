#include "ModelLoader.h"
#include "./Renderer/Model.h"

namespace mslib {
namespace loader {
std::shared_ptr<render::ModelData> ModelLoader::Load(std::string _fileName) {
	auto& assets = assets::AssetsManager::GetInstance().m_assets[_fileName];
	// •Û‚µ‚Ä‚¢‚é‚©‚Ç‚¤‚©Šm”F
	if (assets.has_value()) {
		return std::any_cast<std::shared_ptr<render::ModelData>>(assets);
	}

	// assets = data;
}

}
}
