#pragma once

#include "./DirectX/DirectX11Manager.h"

namespace mslib {
namespace texture {

class TextureLoder {
public:
	TextureLoder(mslib::directx::Device _device, mslib::directx::DeviceContext _device_context);
	mslib::directx::ShaderTexture Load(const char* filen_name);

	bool CrateTexture();
private:
	mslib::directx::Device m_device;
	mslib::directx::DeviceContext m_device_context;
};

}
}