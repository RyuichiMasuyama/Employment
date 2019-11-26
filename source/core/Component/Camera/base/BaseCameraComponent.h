#pragma once

#include "./Renderer/RenderTerget.h"
#include "./core/Object/Object.h"
#include "../../PostEffect/BasePostEffectComponent.h"

// 前方宣言
namespace  mslib {
namespace render {
class RenderTerget;
}
}

namespace mslib {
namespace component {
class BaseCameraComponent;
using BaseCameraComponentPtr = std::weak_ptr<BaseCameraComponent>;
using BaseCameraComponentSPtr = std::shared_ptr<BaseCameraComponent>;

class BaseCameraComponent :public Component{
	BASE_CLASS_IS(Component)
	friend object::GameObject;
public:
	BaseCameraComponent();
	virtual ~BaseCameraComponent() = default;

	virtual void Initialize() override;
	virtual void Update() override {
		CreateCameraMatrix();
	}

private:
	// スマートポインタで保持
	// カメラの行列
	std::shared_ptr<math::Matrix> m_worldMatrix;

	// カメラのプロジェクション行列
	std::shared_ptr<math::Matrix> m_projectionMatrix;

	// カメラの逆行列
	std::shared_ptr<math::Matrix> m_inversMatrix;

	// プロジェクション行列生成用
	std::shared_ptr<float> m_near;
	std::shared_ptr<float> m_aspect;
	std::shared_ptr<float> m_fov;
	std::shared_ptr<float> m_far;

	// 視点の長さ
	std::shared_ptr<float> m_length;

protected:
	// 新しいレンダーターゲットを生成する
	std::weak_ptr<mslib::render::RenderTerget> m_renderTerget;	

public:
	// セッター
	void SetNear(float _nearclip);

	void SetFar(float _farclip);

	void SetFov(float _fov);

	void SetLength(float _lenght);

	void SetAspect(float _width, float _height);

	//プロジェクション行列設定
	void SetProjection(float _nearclip, float _farclip, float _fov, float _width, float _height);

private:
	//カメラのマトリックスの生成
	void CreateCameraMatrix();

	//カメラのプロジェクションマトリックスの生成
	void CreateProjectionMatrix();

	template<class T>
	std::weak_ptr<T> AddPostEffectComponent() {
		static_assert(std::is_base_of<component::BasePostEffectComponent, T>::value, "ポストエフェクトを設定してください");

		// ポストエフェクトコンポーネントを生成
		// 今後、AddComponentではポストエフェクトを
		// アタッチできないようにしなければいけない
		auto postEffect = m_transform.lock()->m_gameObject.lock()->AddComponent<T>(m_renderTerget);
	}
};

}
}