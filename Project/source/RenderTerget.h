#pragma once

#include "./DirectX/DirectX11Manager.h"
#include "./DirectX/DeviceGetter.h"
#include "./Singleton.h"
#include "./MyDirectXMath.h"
#include <memory>
#include <vector>

namespace mslib {
namespace render {
class DirectXRender;
}
}

namespace mslib {
namespace render {

enum class RenderTergetType{
	NORMAL,
	SUBCAMERA,
	SHADOW_MAP,
	MAX
};

// レンダーターゲット生成
// 自分の見立てだと、レンダーターゲット1つに
// カメラ1つの状態になる
class RenderTerget :public directx::DeviceContextGetter {
	friend class RenderTergetManager;
public:
	RenderTerget() { m_inceNum++; };
	~RenderTerget() = default;

	void SetRenderTerget();
	void SetShaderResorce(int _number);
	mslib::directx::RenderTargetView GetRenderTergetView() { return m_renderTergetView; };

	void SetCameraData(
		std::weak_ptr<math::Matrix> _worldMatrix,
		std::weak_ptr<math::Matrix> _projectionMatrix,
		std::weak_ptr<math::Matrix> _inversMatrix,
		math::Vector3* _position);

protected:
	mslib::directx::RenderTargetView m_renderTergetView;
	mslib::directx::SamplerState m_samplerState;
	mslib::directx::ShaderTexture m_shaderResourceView;
	mslib::directx::Texture2D m_texture2d;

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
	math::Vector3 *m_position;
};

class SubCameraRender :public RenderTerget, directx::DeviceGetter {
public:
	SubCameraRender();
	~SubCameraRender() = default;
};

class ShadowMapRender :public RenderTerget, directx::DeviceGetter {
public:
	ShadowMapRender();
	~ShadowMapRender() = default;
};

class RenderTergetManager :public pattern::Singleton<RenderTergetManager> {
public:
	std::weak_ptr<RenderTerget> CreateRenderTerget(const RenderTergetType _renderType);
	const std::vector<std::shared_ptr<RenderTerget>>& GetRenderTergets() { return m_renderTergets; }

	// レンダーターゲットを渡すと消す処理
	void ElaseRenderTerget(std::weak_ptr<RenderTerget> _renderTerget);

private:
	std::vector<std::shared_ptr<RenderTerget>> m_renderTergets;
};

}
}
