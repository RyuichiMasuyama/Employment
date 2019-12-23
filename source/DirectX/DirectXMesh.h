#pragma once

#include "./Renderer/BaseMesh.h"
#include "./DirectX11Manager.h"

namespace mslib {
namespace directx {
// 前方宣言
class DirectXMesh;
}

namespace render {
// typedef隠蔽
using BasisMesh = directx::DirectXMesh;
}

namespace directx {

class DirectXMesh :public base::BaseMesh {
public:
	DirectXMesh();
	~DirectXMesh() = default;

	// 描画コマンドのみを送る
	// マテリアルやテクスチャのセットはしない
	void Draw()override;
	bool Load(const std::vector<render::PolygonAnimationVertex>& _vecVer, const std::vector<render::PolygonIndex> _vecIndex)override;
private:
	// 各種バッファ
	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;

	bool CreateVertexBuffer(size_t _vertexSize, size_t _vertexNum, void *_vertexFrontAddress);
	bool CreateIndexBuffer(size_t _indexNum, void* _indexFrontAddress);
};

}
}