#pragma once

#include "./Renderer/RenderObject.h"

namespace mslib {
namespace loader {
class MaterialLoader {
public:
	MaterialLoader() = default;
	~MaterialLoader() = default;
	std::shared_ptr <render::Material> LoadMaterial(std::string _materialName);
};
}
}