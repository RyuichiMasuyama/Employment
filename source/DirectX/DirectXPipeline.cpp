#include "./DirectXPipeline.h"
#include "./Renderer/RenderObject.h"
#include "./SubResourceSendManager.h"

namespace mslib {
namespace directx {

void DirectXPipeline::SetVertexPixcle(std::string _vs, std::string _ps) {
	shader::ShaderLoader shaderLoader;
	m_shaderResource.vertexShader = shaderLoader.Load(_vs, shader::ShaderType::VS);
	m_shaderResource.pixelShader = shaderLoader.Load(_ps, shader::ShaderType::PS);
	m_shaderResource.inputLayer = shaderLoader.Load(_ps, shader::ShaderType::IL);
}

void DirectXPipeline::SetGeometory(std::string _gs) {
	shader::ShaderLoader shaderLoader;
	m_shaderResource.geometryShader = shaderLoader.Load(_gs, shader::ShaderType::GS);
}

void DirectXPipeline::SetHullDomainShader(std::string _ds, std::string _hs) {
	shader::ShaderLoader shaderLoader;
	m_shaderResource.domainShader = shaderLoader.Load(_ds, shader::ShaderType::DS);
	m_shaderResource.hullShader = shaderLoader.Load(_hs, shader::ShaderType::HS);
}
//
//// �ʒu���
//directx::SubResourceSendManager::GetInstance().SetWorldObjectBuffer();
void DirectXPipeline::Draw() {
	auto deviceContext = DirectX11Manager::GetInstance().GetDeviceContext();

	//�`��p�̃V�F�[�_�[�⃌�C�A�E�g�A���_�f�[�^�[�𑗐M
	// ���_�t�H�[�}�b�g���Z�b�g
	directx::VertexShader vs;
	directx::PixelShader ps;
	directx::InputLayout layer;
	directx::GeometryShader gs;
	directx::HullShader hs;
	directx::DomainShader ds;
/*
	m_shaderResource.vertexShader .As(&vs);
	m_shaderResource.pixelShader.As(&ps);
	m_shaderResource.inputLayer.As(&layer);
	m_shaderResource.geometryShader.As(&gs);
	m_shaderResource.hullShader.As(&hs);
	m_shaderResource.domainShader.As(&ds);
*/
	deviceContext->IASetInputLayout(layer.Get());

	// ���_�V�F�[�_�[���Z�b�g
	deviceContext->VSSetShader(vs.Get(), nullptr, 0);

	// �s�N�Z���V�F�[�_�[���Z�b�g
	deviceContext->PSSetShader(ps.Get(), nullptr, 0);

	// �T���v���[�X�e�[�g��]��
	// deviceContext->PSSetSamplers(0, 1, render_object.lock()->GetAddressOf());

	//�W�I���g���V�F�[�_�[���Z�b�g
	deviceContext->GSSetShader(gs.Get(), nullptr, 0);

	//�n���V�F�[�_�[���Z�b�g
	deviceContext->HSSetShader(hs.Get(), nullptr, 0);

	//�h���C���V�F�[�_�[���Z�b�g
	deviceContext->DSSetShader(ds.Get(), nullptr, 0);

	//��������������������������������������������������������������������

	//////////////////////////////////////////////////////////////////////
	//					���_�f�[�^�[�Z�b�e�B���O����					//
	//////////////////////////////////////////////////////////////////////
	//��������������������������������������������������������������������

	// ���_�o�b�t�@���Z�b�g����
	unsigned int stride = sizeof(render::Vertex3DModel);
	unsigned  offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, m_vertex_buffer.GetAddressOf(), &stride, &offset);

	//�C���f�b�N�X�o�b�t�@���Z�b�g
	deviceContext->IASetIndexBuffer(m_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	auto material = m_mesh->GetMaterial();
	for (unsigned int i = 0; i < m_texture.size(); i++) {
		ShaderTexture tex;
		//m_texture[i].As(&tex);
		deviceContext->PSSetShaderResources(i, 1, tex.GetAddressOf());
	}

	unsigned int indexCount = static_cast<int>(m_mesh->GetPolygons()->index.size());
	// �`��I�I�I
	deviceContext->DrawIndexed(
		indexCount,					// �C���f�b�N�X�̐�
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0							// ���_�o�b�t�@�̍ŏ�����̈ʒu
	);
}

void DirectXPipeline::CreateVertexBuffer(size_t _vertexSize, size_t _vertexNum,void *_vertexFrontAddress) {
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
		CreateBuffer(&bd, &InitData, m_vertex_buffer.GetAddressOf());		// �o�b�t�@����
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(vertex buffer) error", "Error", MB_OK);
		return;
	}

	return;
}

void DirectXPipeline::CreateIndexBuffer(size_t _indexNum, void* _indexFrontAddress) {
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
		CreateBuffer(&bd, &InitData, m_index_buffer.GetAddressOf());
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(index buffer) error", "Error", MB_OK);
		return;
	}
}

void DirectXPipeline::LoadTexture(std::string _textureName) {
	texture::TextureLoader loader;
	m_texture.push_back(loader.Load(_textureName));
}

}
}