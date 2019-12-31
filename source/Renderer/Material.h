#pragma once

#include "./BaseMaterial.h"
#include <memory>

namespace mslib {
namespace render {
class MyMaterial{
public:
	MyMaterial();
	~MyMaterial() = default;

	void Send();
	MaterialData* GetetMaterial();
private:
	std::unique_ptr< BaseMaterial > m_baseMaterial;
};
}
}