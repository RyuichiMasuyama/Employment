#pragma once

#include <./core/Component/Render/ModelRenderComponent.h>
#include <string>
namespace mslib {
namespace component {
class FeadComponent :public Component{
	BASE_CLASS_IS(Component)
public:
	FeadComponent(std::string _textureNmae);
	~FeadComponent() = default;

	void Initialize()override;

	void SetFeadLevel(float _level);

	void Update()override;

private:
	float m_feadlevel;
	float *m_ambX;
	std::string m_fileName;
	render::ModelData feadModel;
};
}
}