#include "Mesh.h"

#ifdef DIRECTX11
#include "./DirectX/DirectXMesh.h"
#endif

namespace mslib {
namespace render {

Mesh::Mesh() {
	m_basisMeshPtr = std::make_unique< BasisMesh >();
}

void Mesh::Draw() {
	m_basisMeshPtr->Draw();
}

}  // namespace render
}  // namespace mslib