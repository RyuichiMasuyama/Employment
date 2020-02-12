#pragma once

#include <memory>
#include <Assimp\AssimpSecen.h>

namespace mslib {
namespace loader {
class AssimpLoader {
public:
	AssimpLoader() = default;
	~AssimpLoader() = default;
	
	std::shared_ptr <assimp::AssimpScene> Load(std::string _materialName);
};
}
}