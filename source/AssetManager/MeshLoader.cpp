#include "./MeshLoader.h"
#include "./AssetManager.h"

namespace mslib {
namespace mesh {
std::weak_ptr<render::MyMesh> MeshLoader::Load(std::string _fileName){
	auto& asset = assets::AssetsMeshs::GetInstance().m_assets[_fileName];
	// ���g���Ȃ���ΐ�������
	if (asset.use_count() != 0) {
		return asset;
	}

	// �����ƃ��[�h
	asset = std::make_shared<render::MyMesh>();
	asset->Load(_fileName);

	return asset;
}
}
}
