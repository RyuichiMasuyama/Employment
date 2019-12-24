#pragma once
#include <string>
#include <memory>

namespace mslib {
namespace render {
class ModelData;
}
namespace loader {
class ModelLoader {
public:
	ModelLoader() = default;
	~ModelLoader() = default;
	
	std::shared_ptr<render::ModelData> Load(std::string _fileName);
};
}  // namespace loader
}  // namespace mslib