#pragma once

#include "./Renderer/BaseMaterial.h"
#include "./DirectX/SubResourceSendManager.h"
namespace mslib {
namespace directx {
class DirectXMaterial;
}
namespace render {
using BasesMaterial = directx::DirectXMaterial;
}
namespace directx {
// �B���p
class DirectXMaterial :public  render::BaseMaterial {
public:
	DirectXMaterial() = default;
	~DirectXMaterial() = default;

	// ���[�h
	void Load(std::string _fileName) override;
	// GPU���M
	void Send() override;


};
}
}