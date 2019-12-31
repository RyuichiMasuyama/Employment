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
// 隠蔽用
class DirectXMaterial :public  render::BaseMaterial {
public:
	DirectXMaterial() = default;
	~DirectXMaterial() = default;

	// ロード
	void Load(std::string _fileName) override;
	// GPU送信
	void Send() override;


};
}
}