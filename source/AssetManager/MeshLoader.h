#pragma once

#include <string>
#include <memory>

namespace mslib {
namespace render {
class MyMesh;
class Mesh;
}

namespace loader {

class MeshLoader {
public:
	MeshLoader();
	~MeshLoader() = default;

	std::shared_ptr<render::MyMesh> Load(std::string _fileName);
};

}
}