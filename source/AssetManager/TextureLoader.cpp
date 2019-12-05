#include	<locale.h>
#include "./AssetManager/AssetManager.h"
#include "./TextureLoader.h"

#ifdef DIRECTX11
#include "./DirectX/TextureLoader/WICTextureLoader.h"
#endif

namespace mslib {
namespace texture {

Texture TextureLoader::Load(std::string _fileName) {

#ifdef DIRECTX11
	// ���[�h����Ă�ΕԂ�
	auto &asset = assets::AssetsManager::GetInstance().m_assets[_fileName];
	if (asset.has_value()) {
		return std::any_cast<Texture>(asset);
	}

	// ����Ă��Ȃ��̂Ń��[�h����
	HRESULT hr;
	Texture texture;
	char current_path[1024];
	GetCurrentDirectory(1024, current_path);	// �����̃J�����g�t�H���_�̋L�^

	ID3D11Resource*			tex = nullptr;		// �e�N�X�`�����\�[�X
	wchar_t ws[256];
	size_t ret;

	setlocale(LC_CTYPE, "jpn");
	mbstowcs_s(&ret, ws, 256, _fileName.c_str(), _TRUNCATE);

	SetCurrentDirectory(TEXT("assets/texture"));
	//�e�N�X�`���ǂݍ���
	hr = DirectX::CreateWICTextureFromFile(
		directx::DirectX11Manager::GetInstance().GetDevice().Get(),
		directx::DirectX11Manager::GetInstance().GetDeviceContext().Get(),
		ws, &tex, texture.GetAddressOf());

	SetCurrentDirectory(current_path);

	// ���[�h���~�X�����null��Ԃ�
	if (FAILED(hr)) {
		asset = nullptr;
		return nullptr; 
	}
	// ���[�h���ł����̂ŃA�Z�b�gManager�ɃZ�b�g
	asset = texture;
	return texture;
#endif
}

//bool TextureLoader::CrateTexture() {
	//HRESULT result = S_FALSE;
	//D3D11_TEXTURE2D_DESC desc;
	//D3D11_SUBRESOURCE_DATA initialData;
	//ID3D11Texture2D* texture = nullptr;

	//ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	//desc.Width = SCREEN_X;
	//desc.Height = SCREEN_Y;
	//desc.MipLevels = 1;
	//desc.ArraySize = 1;
	//desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//desc.SampleDesc.Count = 1;
	//desc.SampleDesc.Quality = 0;
	//desc.Usage = D3D11_USAGE_DEFAULT;
	//desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
	//desc.CPUAccessFlags = 0;
	//desc.MiscFlags = 0;

	//ZeroMemory(&initialData, sizeof(D3D11_SUBRESOURCE_DATA));
	//// initialData.pSysMem = image;
	//initialData.SysMemPitch = SCREEN_X * 4;

	//result = directx::DirectX11Manager::GetInstance().GetDevice()->CreateTexture2D(&desc, &initialData, &texture);

	//if (result == S_OK) {
	//	return true;
	//}
	//return false;
//}

}
}