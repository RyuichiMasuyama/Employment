#pragma once
#include "./Renderer/RenderObject.h"

#include <string>

namespace mslib {
namespace mesh {

class MeshLoader {
public:
	MeshLoader() = default;
	~MeshLoader() = default;

	std::weak_ptr<render::MyMesh> Load(std::string _fileName);
};

}
}