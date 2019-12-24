#include "Mesh.h"

#ifdef DIRECTX11
#include "./DirectX/DirectXMesh.h"
#endif

namespace mslib {
namespace render {

Mesh::Mesh() {
	m_basisMeshPtr = std::make_unique< BasisMesh >();
}

void Mesh::Load(const std::vector<render::PolygonAnimationVertex>& _vecVer, const std::vector<render::PolygonIndex> _vecIndex) {
	m_basisMeshPtr->Load(_vecVer, _vecIndex);
}

void Mesh::Draw() {
	m_basisMeshPtr->Draw();
}

}  // namespace render
}  // namespace mslib