#pragma once

#include <Singleton.h>
#include <vector>
#include <functional>

#ifdef DIRECTX11
#include "./MyDirectXMath.h"
#endif

#include "./Renderer/RenderTerget.h"
#include "./Renderer/RenderObject.h"
#include "../AssetManager/MeshLoader.h"

// �ő�`�搔
// �p�[�e�B�N���ȊO�H�H
// #define RENDER_MAX 10000

namespace mslib {
namespace render { 
using PipelineFunction = std::function<void(void)>;

class Render;

class RenderObjectCommand {
	friend Render;
private:
	const PipelineFunction m_function;

	Pipeline* m_pipelinePtr;

	math::Matrix& m_mat;

public:
	// �R���X�g���N�^
	/*RenderObjectCommand(math::Matrix& _mat, const PipelineFunction _pipelineFunction) :
		m_mat(_mat), m_function(_pipelineFunction) {};*/
	RenderObjectCommand(math::Matrix& _mat, Pipeline* _pipelinePtr) :
		m_mat(_mat), m_pipelinePtr(_pipelinePtr) {};
};

class Render :public pattern::Singleton<Render>{
public:
	Render() { 
		mesh::MeshLoader meshLoader;
		m_rendering = meshLoader.Load("Quad");
	};
	~Render() = default;

	// command��ێ�����
	void Draw( math::Matrix& _mat, Pipeline* _pipelineFunction);
	
	void Rendering();
	void ImGuiCare();
	void AfterCare();

private:
	std::vector<RenderObjectCommand> m_commandDynamicArray;

	std::shared_ptr<MyMesh> m_rendering;
};

}
}