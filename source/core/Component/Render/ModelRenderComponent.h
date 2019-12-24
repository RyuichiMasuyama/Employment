#pragma once

#include "./core/Object/Object.h"
#include "./Renderer/Render.h"
#include "./Renderer/Model.h"

namespace mslib {
namespace render {
class ModelData;
}

namespace component {

class ModelRenderComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	ModelRenderComponent(std::shared_ptr<render::ModelData> _model) :m_model(_model) {}

	void FixedUpdate()override;

private:
	std::shared_ptr<render::ModelData> m_model;
};

}
}