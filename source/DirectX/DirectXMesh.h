#pragma once

#include "./Renderer/BaseMesh.h"
#include "./DirectX11Manager.h"

namespace mslib {
namespace directx {
// �O���錾
class DirectXMesh;
}

namespace render {
// typedef�B��
using BasisMesh = directx::DirectXMesh;
}

namespace directx {

class DirectXMesh :public base::BaseMesh {
public:
	DirectXMesh();
	~DirectXMesh() = default;

	// �`��R�}���h�݂̂𑗂�
	// �}�e���A����e�N�X�`���̃Z�b�g�͂��Ȃ�
	void Draw()override;
	bool Load(const std::vector<render::PolygonAnimationVertex>& _vecVer, const std::vector<render::PolygonIndex> _vecIndex)override;
private:
	// �e��o�b�t�@
	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;

	bool CreateVertexBuffer(size_t _vertexSize, size_t _vertexNum, void *_vertexFrontAddress);
	bool CreateIndexBuffer(size_t _indexNum, void* _indexFrontAddress);
};

}
}