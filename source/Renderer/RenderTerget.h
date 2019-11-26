#pragma once

#include "./Singleton.h"
#include "./MyDirectXMath.h"
#include <memory>
#include <vector>

#ifdef DIRECTX11
//#include "./DirectX/DirectXRenderTerget.h"
#endif


namespace mslib {

#ifdef DIRECTX11
namespace directx {
class DirectXRenderTerget;
}
#endif

namespace render {

#ifdef DIRECTX11
using RendringSoftRenderTergetPtr = std::weak_ptr< directx::DirectXRenderTerget >;
#endif

struct PostEffect;

enum class RenderTergetType :unsigned int{
	MAIN,
	SUBCAMERA,
	SHADOW_MAP,
	MAX
};

// レンダーターゲット生成
// 自分の見立てだと、レンダーターゲット1つに
// カメラ1つの状態になる
class RenderTerget {
	friend class RenderTergetManager;
public:
	RenderTerget(RenderTergetType _renderTergetType) :m_renderTergetType(_renderTergetType) {
		static unsigned int inc = 0;
		m_inceNum = inc;
		inc++;
	};
	~RenderTerget();	// unique_ptr使用のため非インライン化

	void Initalize(RendringSoftRenderTergetPtr _softRenderTerget);

	void SetRenderTerget();
	void SetShaderResorce(int _number);
	// mslib::directx::RenderTargetView GetRenderTergetView() { return m_renderTergetView; };

	void SetCameraData(
		std::weak_ptr<math::Matrix> _worldMatrix,
		std::weak_ptr<math::Matrix> _projectionMatrix,
		std::weak_ptr<math::Matrix> _inversMatrix,
		math::Vector3* _position);

	void SetPostEffectData(std::weak_ptr<PostEffect> _postEffect);

	void Pipeline();

private:
	unsigned int m_inceNum;
	// カメラの情報を保持
	// カメラの行列
	std::weak_ptr<math::Matrix> m_worldMatrix;

	// カメラのプロジェクション行列
	std::weak_ptr<math::Matrix> m_projectionMatrix;

	// カメラの逆行列
	std::weak_ptr<math::Matrix> m_inversMatrix;

	// 位置情報
	// RT(1)--(1)Cameraの関係なので生ポでOK
	math::Vector3 *m_position;

	// ポストエフェクトのデーター
	// RT(1)--(0?1)PostEffecなので
	// 保持を確認
	std::weak_ptr<PostEffect> m_postEffect;

	RenderTergetType m_renderTergetType; 

	RendringSoftRenderTergetPtr m_softRenderTerget;
};

class RenderTergetManager :public pattern::Singleton<RenderTergetManager> {
public:
	std::weak_ptr<RenderTerget> CreateRenderTerget(const RenderTergetType _renderType);
	const std::vector<std::shared_ptr<RenderTerget>>& GetRenderTergets() { return m_renderTergets; }
	const std::vector < std::weak_ptr<RenderTerget>>& GetRenderTergets(const RenderTergetType _renderType);
	// レンダーターゲットを渡すと消す処理
	void ElaseRenderTerget(std::weak_ptr<RenderTerget> _renderTerget);

private:
	std::vector<std::shared_ptr<RenderTerget>> m_renderTergets;

	// カメラのタイプが変わったら追加
	std::vector<std::weak_ptr<RenderTerget>> m_shadowMapRender;
	std::vector<std::weak_ptr<RenderTerget>> m_subCameraRender;
	std::vector<std::weak_ptr<RenderTerget>> m_mainCameraRender;
};

}
}
