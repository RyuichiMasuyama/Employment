#pragma once

#include "./core/Object/Object.h"
#include "./Renderer/Render.h"
#include "../../../AssetManager/ShaderLoader.h"

namespace mslib {
namespace render {
class MyMesh;
}

namespace component {

class RenderComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	RenderComponent(std::shared_ptr<render::MyMesh> _mesh) :m_mesh(*_mesh) {}

	void FixedUpdate()override;

	// �V�F�[�_�[�ύX�E�e�N�X�`���ύX
	void SetShader(std::string _shaderName, shader::ShaderType _shaderType);
	void SetTexture(std::string _textureName, int _number);

private:
	render::MyMesh m_mesh;
};

}
}