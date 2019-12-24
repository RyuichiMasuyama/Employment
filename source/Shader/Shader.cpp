#include "./Shader/Shader.h"
#include "./AssetManager/AssetManager.h"

#ifdef DIRECTX11
#include "./ShaderCompiler.h"
#endif

namespace mslib {
namespace directx {


ID3D11Buffer* BufferCreater::CreateConstantBuffer(UINT _byte_size)
{
	// �R���X�^���g�o�b�t�@�����p�f�X�N
	D3D11_BUFFER_DESC bd;

	//�R���X�^���g�o�b�t�@
	ID3D11Buffer* buffer;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;								// �o�b�t�@�g�p���@
	bd.ByteWidth = _byte_size;									// �o�b�t�@�̑傫
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;					// �R���X�^���g�o�b�t�@
	bd.CPUAccessFlags = 0;										// CPU�A�N�Z�X�s�v

	HRESULT hr = m_device->CreateBuffer(&bd, nullptr, &buffer);
	if (FAILED(hr)) {
		MessageBox(nullptr, "CreateBuffer(constant buffer) error", "Error", MB_OK);
		return nullptr;
	}

	return buffer;
}

ID3D11Buffer * BufferCreater::CreateIndexBuffer(UINT* _index, UINT _index_num)
{
	//�C���f�b�N�X�o�b�t�@�쐬
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth = sizeof(UINT) * _index_num;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subresource_data;
	ZeroMemory(&subresource_data, sizeof(subresource_data));
	subresource_data.pSysMem = _index;

	ID3D11Buffer* buffer;
	if (FAILED(m_device->CreateBuffer(&buffer_desc, &subresource_data, &buffer))) {
		return nullptr;
	}
	return buffer;
}

}

namespace shader{
void Shaders::Send() {
	auto deviceContext = directx::DirectX11Manager::GetInstance().GetDeviceContext();

	//�`��p�̃V�F�[�_�[�⃌�C�A�E�g�A���_�f�[�^�[�𑗐M
	// ���_�t�H�[�}�b�g���Z�b�g
	deviceContext->IASetInputLayout(m_inputLayout.Get());

	// ���_�V�F�[�_�[���Z�b�g
	deviceContext->VSSetShader(m_vertexShader.Get(), nullptr, 0);

	// �s�N�Z���V�F�[�_�[���Z�b�g
	deviceContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	//// �T���v���[�X�e�[�g��]��
	//deviceContext->PSSetSamplers(0, 1, .lock()->GetAddressOf());

	//�W�I���g���V�F�[�_�[���Z�b�g
	deviceContext->GSSetShader(m_geometryShader.Get(), nullptr, 0);

	//�n���V�F�[�_�[���Z�b�g
	deviceContext->HSSetShader(m_hullShader.Get(), nullptr, 0);

	//�h���C���V�F�[�_�[���Z�b�g
	deviceContext->DSSetShader(m_domainShader.Get(), nullptr, 0);
}
void Shaders::SetVertexShader(VertexShader _shader) {
	m_vertexShader = _shader;
}
void Shaders::SetPixelShader(PixelShader _shader) {
	m_pixelShader = _shader;
}
void Shaders::SetGeometryShader(GeometryShader _shader) {
	m_geometryShader = _shader;
}
void Shaders::SetDomainShader(DomainShader _shader) {
	m_domainShader = _shader;
}
void Shaders::SetHullShader(HullShader _shader) {
	m_hullShader = _shader;
}
void Shaders::SetInputLayout(InputLayer _inputLayout) {
	m_inputLayout = _inputLayout;
}
}
}

