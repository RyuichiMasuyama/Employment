#pragma once

#include "./DirectX/DirectX11Manager.h"
#include "MyDirectXMath.h"

namespace mslib {
namespace Light {
class ParallelLight {
private:
	struct ParalleLightConstantBuffer {
		math::Vector4 way;
	};

	math::Vector4 m_way;
	mslib::directx::ConstantBuffer buff;

	mslib::directx::DeviceContext m_device_context;

public:
	ParallelLight(mslib::directx::Device _device, mslib::directx::DeviceContext _device_context);

	void Update();

	void SetWay(math::Vector4 _way) { m_way = _way; };
};

namespace Library {

}
}
}