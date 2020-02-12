#include "./Texture.h"

#ifdef DIRECTX11
#include "./DirectX/DirectXTexture.h"
#endif // DIRECTX11

namespace mslib {
namespace texture {
MyTexture::MyTexture() {
	m_baseTexture = std::make_unique<texture::BasisTexture>();
}
void MyTexture::Send(int _number) {
	if(m_baseTexture)	m_baseTexture->Send(_number);
}

void MyTexture::Load(std::string _fileNmae) {
	m_baseTexture->Load(_fileNmae);
}

}
}


