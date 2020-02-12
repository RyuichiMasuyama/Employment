#pragma once

#include "./BaseMaterial.h"
#include <memory>

namespace mslib {
namespace render {
class MyMaterial{
public:
	MyMaterial();
	~MyMaterial() = default;

	// GPU送信
	void Send();
	
	// マテリアルの取得
	// AssetManagerから取得する
	void Load(std::string _materialName) {};

	// マテリアルの取得
	MaterialData* GetMaterial();

	// マテリアルのセット
	void SetMaterial(const MaterialData& _material);
private:
	std::unique_ptr< BaseMaterial > m_baseMaterial;
};
}
}