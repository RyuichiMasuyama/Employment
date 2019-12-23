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
	// ���g���Ȃ���ΐ�������
	if (asset.has_value()) {
		return std::any_cast<std::shared_ptr<render::MyMesh>>(asset);
	}

	// �����ƃ��[�h
	auto loadModel= std::make_shared<render::MyMesh>();

	// ���[�h
	loadModel->Load(_fileName);

	// �Q�Ƃɓn���Đ����������b�V������
	asset = loadModel;

	// �V�F�A�[�h�̃��b�V����Ԃ�
	return loadModel;
}
std::shared_ptr<render::Mesh> MeshLoader::Load(std::string _fileName, int test) {

	return std::shared_ptr<render::Mesh>();
}
}
}
