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

// 最大描画数
// パーティクル以外？？
// #define RENDER_MAX 10000

namespace mslib {
namespace render { 
using PipelineFunction = std::function<void(void)>;

// モデルのポインタを渡すための前方宣言
class ModelData;

class Render;

class RenderObjectCommand {
	friend Render;
private:
	const PipelineFunction m_function;
	ModelData* m_modelDataPtr;
	// Pipeline* m_pipelinePtr;

	math::Matrix& m_mat;

public:
	// コンストラクタ
	/*RenderObjectCommand(math::Matrix& _mat, const PipelineFunction _pipelineFunction) :
		m_mat(_mat), m_function(_pipelineFunction) {};*/
		//RenderObjectCommand(math::Matrix& _mat, Pipeline* _pipelinePtr) :
		//	m_mat(_mat), m_pipelinePtr(_pipelinePtr) {};
	RenderObjectCommand(math::Matrix&_mat, ModelData*_modelDataPtr);
};

class Render :public pattern::Singleton<Render>{
public:
	Render() { 
		loader::MeshLoader meshLoader;
		m_rendering = meshLoader.Load("Quad");
	};
	~Render() = default;

	// commandを保持する
	void Draw( math::Matrix& _mat, ModelData* _modelData);
	
	void Rendering();
	void ImGuiCare();
	//void AfterCare();

private:
	std::vector<RenderObjectCommand> m_commandDynamicArray;

	std::shared_ptr<MyMesh> m_rendering;
};

}
}