#include "./DirectXMesh.h"
#include "./DirectX11Manager.h"

namespace mslib {
namespace directx {

DirectXMesh::DirectXMesh() {
}

void DirectXMesh::Draw() {
	auto deviceContext = DirectX11Manager::GetInstance().GetDeviceContext();

	// 頂点バッファをセットする
	unsigned int stride = sizeof(render::PolygonVertex);
	unsigned  offset = 0;

	// バーテックスバッファをセット
	deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);

	// インデックスバッファをセット
	deviceContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	int indexCount = static_cast<int>(m_index.size());

	// 描画コマンド
	deviceContext->DrawIndexed(
		indexCount,					// インデックスの数
		0,							// 最初のインデックスバッファの位置
		0							// 頂点バッファの最初からの位置
	);
}

//bool DirectXMesh::AnimationLoad(const std::vector<render::PolygonAnimationVertex>& _vecWight) {
//	m_animationWight = _vecWight;
//	auto verIndexSize = _vecWight.size();
//	CreateVertexBuffer(sizeof(m_vertex[0]), verVecSize, (void*)&m_vertex[0]);
//	return false;
//}

bool DirectXMesh::Load(const std::vector<render::PolygonAnimationVertex>& _vecVer, const std::vector<render::PolygonIndex>_vecIndex) {
	m_animationWight = _vecVer;
	m_index = _vecIndex;

	auto verVecSize = _vecVer.size();
	auto verIndexSize = _vecIndex.size();

	// (void*)はstatic_castはしない
	auto ans1 = CreateVertexBuffer(sizeof(m_animationWight[0]), verVecSize, (void*)&m_animationWight[0]);
	auto ans2 = CreateIndexBuffer(verIndexSize, (void*)&m_index[0]);

	// 両方とも成功すればtrue
	return ans1 && ans2;
}

bool DirectXMesh::CreateVertexBuffer(size_t _vertexSize, size_t _vertexNum, void * _vertexFrontAddress) {
	HRESULT hr;

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;							// バッファ使用方法
	bd.ByteWidth = static_cast<UINT>(_vertexSize * _vertexNum);						// バッファの大きさ
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// 頂点バッファ
	bd.CPUAccessFlags = 0;									// CPUアクセス不要

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _vertexFrontAddress;							// バッファの初期値

	hr = DirectX11Manager::GetInstance().GetDevice()->
		CreateBuffer(&bd, &InitData, m_vertexBuffer.GetAddressOf());		// バッファ生成
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}

	return true;
}

bool DirectXMesh::CreateIndexBuffer(size_t _indexNum, void * _indexFrontAddress) {
	// インデックスバッファ生成
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;								// バッファ使用方
	bd.ByteWidth = sizeof(unsigned int) * static_cast<UINT>(_indexNum);				// バッファの大き
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;						// インデックスバッファ
	bd.CPUAccessFlags = 0;										// CPUアクセス不要

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _indexFrontAddress;

	HRESULT hr = DirectX11Manager::GetInstance().GetDevice()->
		CreateBuffer(&bd, &InitData, m_indexBuffer.GetAddressOf());
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(index buffer) error", "Error", MB_OK);
		return false;
	}
	return true;
}


}
}