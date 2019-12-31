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
	ModelRenderComponent(render::ModelData* _model) :m_model(_model) { m_after = false; }

	void FixedUpdate()override;

	void AfterFlagOn();
private:
	render::ModelData* m_model;
	bool m_after;
};

}
}