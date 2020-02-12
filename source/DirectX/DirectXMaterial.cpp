#include "DirectXMaterial.h"
#include "./SubResourceSendManager.h"

namespace mslib {
namespace directx {

void DirectXMaterial::Load(std::string _fileName) {
}

void DirectXMaterial::Send() {
	SubResourceSendManager::GetInstance().SetMaterialBuffer(m_materialData);
}

}
}

