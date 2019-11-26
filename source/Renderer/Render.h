#pragma once

#include <Singleton.h>
#include <vector>
#include <functional>

#ifdef DIRECTX11
#include "./MyDirectXMath.h"
#endif

#include "./Renderer/RenderTerget.h"
#include "./Renderer/RenderObject.h"

// �ő�`�搔
// �p�[�e�B�N���ȊO�H�H
// #define RENDER_MAX 10000

namespace mslib {
namespace render { 
using PipelineFunction = std::function<void(void)>;
class RenderObjectCommand {
private:
	const PipelineFunction m_function;

	const math::Matrix& m_mat;

public:
	// �R���X�g���N�^
	RenderObjectCommand(const math::Matrix& _mat,const PipelineFunction _pipelineFunction) :
		m_mat(_mat), m_function(_pipelineFunction) {};
};

class Render :public pattern::Singleton<Render>{
public:
	Render() = default;
	~Render() = default;

	// command��ێ�����
	void Draw(const math::Matrix& _mat, Pipeline* _pipelineFunction);
	
private:
	std::vector<RenderObjectCommand> m_commandDynamicArray;
};

}
}