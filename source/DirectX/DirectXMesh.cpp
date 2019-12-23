#include "./DirectXMesh.h"
#include "./DirectX11Manager.h"

namespace mslib {
namespace directx {

DirectXMesh::DirectXMesh() {
}

void DirectXMesh::Draw() {
	auto deviceContext = DirectX11Manager::GetInstance().GetDeviceContext();

	// ���_�o�b�t�@���Z�b�g����
	unsigned int stride = sizeof(render::PolygonVertex);
	unsigned  offset = 0;

	// �o�[�e�b�N�X�o�b�t�@���Z�b�g
	deviceContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);

	// �C���f�b�N�X�o�b�t�@���Z�b�g
	deviceContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	int indexCount = static_cast<int>(m_index.size());

	// �`��R�}���h
	deviceContext->DrawIndexed(
		indexCount,					// �C���f�b�N�X�̐�
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0							// ���_�o�b�t�@�̍ŏ�����̈ʒu
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

	// (void*)��static_cast�͂��Ȃ�
	auto ans1 = CreateVertexBuffer(sizeof(m_animationWight[0]), verVecSize, (void*)&m_animationWight[0]);
	auto ans2 = CreateIndexBuffer(verIndexSize, (void*)&m_index[0]);

	// �����Ƃ����������true
	return ans1 && ans2;
}

bool DirectXMesh::CreateVertexBuffer(size_t _vertexSize, size_t _vertexNum, void * _vertexFrontAddress) {
	HRESULT hr;

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;							// �o�b�t�@�g�p���@
	bd.ByteWidth = static_cast<UINT>(_vertexSize * _vertexNum);						// �o�b�t�@�̑傫��
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;				// ���_�o�b�t�@
	bd.CPUAccessFlags = 0;									// CPU�A�N�Z�X�s�v

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = _vertexFrontAddress;							// �o�b�t�@�̏����l

	hr = DirectX11Manager::GetInstance().GetDevice()->
		CreateBuffer(&bd, &InitData, m_vertexBuffer.GetAddressOf());		// �o�b�t�@����
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return false;
	}

	return true;
}

bool DirectXMesh::CreateIndexBuffer(size_t _indexNum, void * _indexFrontAddress) {
	// �C���f�b�N�X�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA InitData;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;								// �o�b�t�@�g�p��
	bd.ByteWidth = sizeof(unsigned int) * static_cast<UINT>(_indexNum);				// �o�b�t�@�̑傫
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;						// �C���f�b�N�X�o�b�t�@
	bd.CPUAccessFlags = 0;										// CPU�A�N�Z�X�s�v

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