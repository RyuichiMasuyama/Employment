#include "./MeshLoader.h"
#include "./AssetManager.h"
#include "./MeshPrimitive.h"
#include "./Assimp/AssimpSecen.h"

namespace mslib {
namespace loader {
MeshLoader::MeshLoader() {
	std::shared_ptr<render::MyMesh> upcastMesh = std::make_shared<Primitive::QuadPrimitive>();
	assets::AssetsManager::GetInstance().m_assets["Quad"] = upcastMesh;
}

std::shared_ptr<render::MyMesh> MeshLoader::Load(std::string _fileName){
	auto& asset = assets::AssetsManager::GetInstance().m_assets[_fileName];
	// 中身がなければ生成する
	if (asset.has_value()) {
		return std::any_cast<std::shared_ptr<render::MyMesh>>(asset);
	}

	// 生成とロード
	auto loadModel= std::make_shared<render::MyMesh>();

	// ロード
	loadModel->Load(_fileName);

	// 参照に渡して生成したメッシュを代入
	asset = loadModel;

	// シェアードのメッシュを返す
	return loadModel;
}
std::shared_ptr<render::Mesh> MeshLoader::Load(std::string _fileName, int test) {

	return std::shared_ptr<render::Mesh>();
}
}
}
