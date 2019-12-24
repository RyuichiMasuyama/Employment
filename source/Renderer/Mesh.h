#pragma once

#include <string>
#include <memory>
#include "./BaseMesh.h"

namespace mslib {
namespace render {

// メッシュ頂点情報などを保持
class Mesh {
public:
	// コンストラクタ・デストラクタ
	Mesh();
	~Mesh() = default;

	// メッシュDataのロード
	void Load(const std::vector<render::PolygonAnimationVertex>& _vecVer, const std::vector<render::PolygonIndex> _vecIndex);

	// 描画
	// 各APIによって変更される
	void Draw();

private:
	// 基底で中継クラス隠蔽
	std::unique_ptr< base::BaseMesh > m_basisMeshPtr;
};

}  // namespace render
}  // namespace mslib