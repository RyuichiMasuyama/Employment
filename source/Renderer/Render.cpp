#include "./Render.h"
#include <algorithm>
#include <functional>
#include "./DirectX/DirectXPipeline.h"

namespace mslib {
namespace render {

void Render::Draw(const math::Matrix& _mat,  Pipeline* _pipelineFunction) {
	RenderObjectCommand command(_mat, std::bind(&Pipeline::Draw, _pipelineFunction));
	m_commandDynamicArray.push_back(command);
}

}
}