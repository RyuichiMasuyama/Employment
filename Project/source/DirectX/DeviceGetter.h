#pragma once
#include "./DirectX/DirectX11Manager.h"

namespace mslib {
namespace directx {
class DeviceGetter {
public:
	DeviceGetter() = default;
	DeviceGetter(Device _device) {
		m_device = _device;
	} 
protected:
	static Device m_device;
};

class DeviceContextGetter {
public:
	DeviceContextGetter() = default;
	DeviceContextGetter(DeviceContext _deviceContext) {
		m_deviceContext = _deviceContext;
	}
protected:
	static DeviceContext m_deviceContext;
};
}
}