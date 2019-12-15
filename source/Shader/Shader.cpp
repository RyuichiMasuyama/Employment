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

//�e��V�F�[�_�[�̐���
//void ShaderWark::Create() {
//	//�o�[�e�b�N�X�V�F�[�_�[
//	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "normal_vs", "shader/testvs.fx");
//	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "2d_vs", "shader/vs2d.fx");
//	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "gauss_vs", "shader/VSGauss.fx");
//
//	//�s�N�Z���V�F�[�_�[
//	m_pixel_manager.CreateShader("normal_ps", "shader/pstest.fx");
//	m_pixel_manager.CreateShader("2d_ps", "shader/ps2d.fx");
//	m_pixel_manager.CreateShader("gauss_ps", "shader/PSGauss.fx");
//
//	//�W�I���g���V�F�[�_�[
//	m_geometry_manager.CreateShader("normal_gs", "shader/Geometry/gs.fx");
//
//	// �|�X�g�G�t�F�N�g�V�F�[�_�[
//	// Gauss
//	m_vertex_manager.CreateShader(shader::INPUT_LAYOUT_NAME::INPUT_LAYOUT_POS_NORMAL_TANGENT_TEXCOORD, "Gauss", "shader/VSGauss.fx");
//	m_pixel_manager.CreateShader("Gauss", "shader/PSGauss.fx");
//
//	// Bloom
//
//}
}

namespace shader{

Shader ShaderLoader::Load(std::string _shaderName, ShaderType _shaderType) {

#ifdef  DIRECTX11
	auto a = std::any_cast<directx::PixelShader>(assets::AssetsManager::GetInstance().m_assets[_shaderName]);
	if (a) {
		return a;
	}
	Shader weakShader;
	auto &asset = assets::AssetsManager::GetInstance().m_assets[_shaderName];
	directx::ShaderCompiler shaderCompiler;

	switch (_shaderType)
	{
	case ShaderType::VS:
		asset = shaderCompiler.Load(_shaderName, directx::ShaderType::VS);
		break;
	case ShaderType::PS: {
		auto aaa = shaderCompiler.Load(_shaderName, directx::ShaderType::PS);

		weakShader = (ID3D11PixelShader*)aaa.Get();// = (ID3D11PixelShader*)shaderCompiler.Load(_shaderName, directx::ShaderType::PS).Get();
		// shaderCompiler.Load(_shaderName, directx::ShaderType::PS);
		break; }
	case ShaderType::GS:
		asset = shaderCompiler.Load(_shaderName, directx::ShaderType::GS);
		break;
	case ShaderType::HS:
		asset = shaderCompiler.Load(_shaderName, directx::ShaderType::HS);
		break;
	case ShaderType::DS:
		asset = shaderCompiler.Load(_shaderName, directx::ShaderType::DS);
		break;
	default:
		break;
	}
	//Shader weakShader;

	// assets::AssetsManager::GetInstance().m_assets[_shaderName] = asset;
	//asset.AsWeak(&weakShader);

	return weakShader;
#endif
}

}
}

