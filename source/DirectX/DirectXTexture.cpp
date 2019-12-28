#include "./DirectXTexture.h"
#include "./AssetManager/TextureLoader.h" 

namespace mslib {
namespace directx {

bool DirectXTexture::Load(std::string _fileName) {
	loader::TextureLoader textureLoader;
	m_texture = textureLoader.Load(_fileName);
	return false;
}

void DirectXTexture::Send(unsigned int _number) {
	auto deviceContext = DirectX11Manager::GetInstance().GetDeviceContext();
	deviceContext->PSSetShaderResources(_number, 1, m_texture.GetAddressOf());
}

}  // namespace directx
}  // namespace mslib
