#include "./Shader/Shader.h"

namespace mslib {
namespace directx {

HRESULT CompileShaderFromFile(const char * _file_name, LPCSTR _main_fanction_name, LPCSTR _shader_version, ID3DBlob ** _compile_shader)
{
	//�R���p�C���������������ۂ�
	HRESULT hr = S_OK;

	//wchar_t�ɕϊ����邽�߂̕ϐ�
	wchar_t file_name[SHADER_NAME_MAX];
	UINT	name_len = 0;

	//char ���� wchar_t�@�֕ϊ�
	setlocale(LC_ALL, "japanese");
	mbstowcs_s(&name_len, file_name, SHADER_NAME_MAX, _file_name, _TRUNCATE);

	DWORD shader_flag = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG)||defined(_DEBUG)
	shader_flag |= D3DCOMPILE_DEBUG;
#endif // defined(DEBUG)||defined(_DEBUG)/

	//�R���p�C���V�F�[�_�[(Error���o)
	ID3DBlob *blob_error = nullptr;

	//�V�F�[�_�[�̃R���p�C��
	hr = D3DCompileFromFile(
		file_name,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_main_fanction_name,
		_shader_version,
		shader_flag,
		0,
		_compile_shader,
		&blob_error
	);

	if (FAILED(hr)) {

		if (blob_error != nullptr) {
			MessageBox(
				NULL,
				(char*)blob_error->GetBufferPointer(), "ShaderCompileError", MB_OK);
		}
		if (blob_error) {
			blob_error->Release();
		}
		return hr;
	}

	return S_OK;

}

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

//�e��V�F�[�_�[�̐���
void ShaderWark::Create() {
	//�o�[�e�b�N�X�V�F�[�_�[
	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "normal_vs", "shader/testvs.fx");
	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "2d_vs", "shader/vs2d.fx");
	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "gauss_vs", "shader/VSGauss.fx");

	//�s�N�Z���V�F�[�_�[
	m_pixel_manager.CreateShader("normal_ps", "shader/pstest.fx");
	m_pixel_manager.CreateShader("2d_ps", "shader/ps2d.fx");
	m_pixel_manager.CreateShader("gauss_ps", "shader/PSGauss.fx");

	//�W�I���g���V�F�[�_�[
	m_geometry_manager.CreateShader("normal_gs", "shader/Geometry/gs.fx");

	// �|�X�g�G�t�F�N�g�V�F�[�_�[
	// Gauss
	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "Gauss", "shader/VSGauss.fx");
	m_pixel_manager.CreateShader("Gauss", "shader/PSGauss.fx");

	// Bloom

}

}
}
