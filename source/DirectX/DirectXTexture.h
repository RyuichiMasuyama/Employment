#pragma once
#include "./DirectX11Manager.h"
#include"./Renderer/BaseTexture.h"
namespace mslib {
namespace directx {
class DirectXTexture :public base::BaseTexture {
public:
	DirectXTexture() = default;
	~DirectXTexture() = default;

	// ‰æ‘œ‚Ìƒ[ƒh
	bool Load(std::string _fileName) override;
	// GPU‘—M
	void Send(unsigned int _number)override;
private:
	ShaderTexture m_texture;
};

}  // namespace directx
// ‰B•Á
namespace texture {
using BasisTexture = directx::DirectXTexture;
}  // namespace texture
}  // namespace mslib