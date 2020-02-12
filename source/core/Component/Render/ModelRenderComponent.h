#pragma once

#include "./core/Object/Object.h"
#include "./Renderer/Render.h"
#include "./Renderer/Model.h"

namespace mslib {
namespace component {

class ModelRenderComponent;
using ModelRenderComponentPtr = std::weak_ptr<ModelRenderComponent>;
using ModelRenderComponentSPtr = std::shared_ptr<ModelRenderComponent>;

class ModelRenderComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	ModelRenderComponent(render::ModelData* _model) :m_model(_model) { m_after = false; }

	void Initialize()override;

	void FixedUpdate()override;

	void AfterFlagOn();
private:
	render::ModelData* m_model;
	bool m_after;
};

}
}