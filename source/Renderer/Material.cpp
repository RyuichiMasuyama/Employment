#include "./Material.h"

#ifdef DIRECTX11
#include "./DirectX/DirectXMaterial.h"
#endif

namespace mslib {
namespace render {
MyMaterial::MyMaterial() {
	m_baseMaterial = std::make_unique<BasesMaterial>();
}
void MyMaterial::Send() {
	m_baseMaterial->Send();
}
MaterialData * MyMaterial::GetMaterial() {
	return &m_baseMaterial->m_materialData;
}
void MyMaterial::SetMaterial(const MaterialData & _material) {
	m_baseMaterial->m_materialData = _material;
}
}
}


