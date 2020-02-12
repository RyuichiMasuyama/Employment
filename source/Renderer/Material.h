#pragma once

#include "./BaseMaterial.h"
#include <memory>

namespace mslib {
namespace render {
class MyMaterial{
public:
	MyMaterial();
	~MyMaterial() = default;

	// GPU���M
	void Send();
	
	// �}�e���A���̎擾
	// AssetManager����擾����
	void Load(std::string _materialName) {};

	// �}�e���A���̎擾
	MaterialData* GetMaterial();

	// �}�e���A���̃Z�b�g
	void SetMaterial(const MaterialData& _material);
private:
	std::unique_ptr< BaseMaterial > m_baseMaterial;
};
}
}