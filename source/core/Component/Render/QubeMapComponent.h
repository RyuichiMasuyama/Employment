#pragma once

#include "./core/Object/object.h"
#include "./ModelRenderComponent.h"

namespace mslib {
namespace component {

class QubeMapComponent;
using QubeMapComponentPtr = std::weak_ptr<QubeMapComponent>;
using QubeMapComponentSPtr = std::shared_ptr<QubeMapComponent>;

class QubeMapComponent :public component::Component {
	BASE_CLASS_IS(Component)
public:

	QubeMapComponent(std::string _mapTextureName);
	~QubeMapComponent() = default;

	void Initialize() override;

private:
	std::string m_mapTextureName;
	render::ModelData m_modelData;
};

}  // namespace component
}  // namespace mslib