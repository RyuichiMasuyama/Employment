#pragma once

#include "./core/Object/Object.h"
#include "./Renderer/Render.h"

// 現在はすべて3Dのvertexを使用して2Dも再現しているが
// 今後、2Dのvertexを作成して対応させるつもりなので
// 一応、Render2DComponentを生成しておく。2Dにするものは
// このコンポーネントを通してレンダリングすること

namespace mslib {
namespace render {
class MyMesh;
}
namespace component {

class Render2DComponent :public Component {
	BASE_CLASS_IS(Component)
public:
	Render2DComponent(std::weak_ptr<render::MyMesh> _mesh) { m_mesh = _mesh; }

	void FixedUpdate()override;


private:
	std::weak_ptr<render::MyMesh> m_mesh;
};

}
}