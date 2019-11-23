#include "DirectXTextureManager.h"
#include "./TextureLoader/WICTextureLoader.h"
#include "./Windows/WindowsDefineData.h"
#include	<locale.h>

namespace mslib {
namespace texture {
TextureLoder::TextureLoder(mslib::directx::Device _device, mslib::directx::DeviceContext _device_context) :
	m_device(_device), m_device_context(_device_context) {
}

mslib::directx::ShaderTexture TextureLoder::Load(const char * filen_name) {
	HRESULT hr;
	mslib::directx::ShaderTexture texture;
	char current_path[1024];
	GetCurrentDirectory(1024, current_path);	// 当初のカレントフォルダの記録

	ID3D11Resource*			tex = nullptr;		// テクスチャリソース
	wchar_t ws[256];
	size_t ret;

	setlocale(LC_CTYPE, "jpn");
	mbstowcs_s(&ret, ws, 256, filen_name, _TRUNCATE);

	SetCurrentDirectory(TEXT("assets/texture"));
	//テクスチャ読み込み
	hr = DirectX::CreateWICTextureFromFile(m_device.Get(), m_device_context.Get(), ws, &tex, texture.GetAddressOf());

	SetCurrentDirectory(current_path);

	if (FAILED(hr))
		return nullptr;

	return texture;
}

bool TextureLoder::CrateTexture() {
	HRESULT result = S_FALSE;
	D3D11_TEXTURE2D_DESC desc;
	D3D11_SUBRESOURCE_DATA initialData;
	ID3D11Texture2D* texture = nullptr;

	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = SCREEN_X;
	desc.Height = SCREEN_Y;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	ZeroMemory(&initialData, sizeof(D3D11_SUBRESOURCE_DATA));
	// initialData.pSysMem = image;
	initialData.SysMemPitch = SCREEN_X * 4;

	result = m_device->CreateTexture2D(&desc, &initialData, &texture);

	if (result == S_OK) {
		return true;
	}
	return false;
}

}
}