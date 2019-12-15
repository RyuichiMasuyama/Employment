#pragma once

#include <string>
#include <memory>

namespace mslib {
namespace render {
class MyMesh;
}

namespace mesh {

class MeshLoader {
public:
	MeshLoader();
	~MeshLoader() = default;

	std::shared_ptr<render::MyMesh> Load(std::string _fileName);
};

}
}