#pragma once

#include <vector>
#include "./Math/Vector.h"

namespace mslib {
namespace render {
// 頂点情報
struct PolygonVertex {
	math::Vector3 pos;
	math::Vector3 normal;
	math::Vector4 color;
	math::Vector3 tangent;
};

// アニメーション頂点情報
struct PolygonAnimationVertex {
	math::Vector3 pos;			// 頂点位置
	math::Vector3 normal;		// 法線
	math::Vector4 color;		// 色
	math::Vector3 tangent;		// タンジェント
	int			  boneIndex[4];	// ウェイトインデックス
	math::Vector4 boneWeight;	// インデックスに対応したウェイト
};

// インデックス
typedef int PolygonIndex;

}  // namespace render
namespace base {

class BaseMesh {
public:
	BaseMesh() = default;
	~BaseMesh() = default;

	// 座標系の違いを補正するため、ロード部分を分ける
	virtual bool Load(const std::vector<render::PolygonAnimationVertex>& _vecVer, const std::vector<render::PolygonIndex> _vecIndex) = 0;
	// アニメーションのデータをロードする
	// virtual bool AnimationLoad(const std::vector<render::PolygonAnimationVertex>& _vecWight) = 0;
	// 描画コマンド送る部分
	virtual void Draw() = 0;
protected:
	// インデックス情報
	std::vector<render::PolygonIndex> m_index;
	// 頂点情報
	// std::vector<render::PolygonVertex> m_vertex;
	// アニメーションがあったらアニメーション情報
	std::vector<render::PolygonAnimationVertex> m_animationWight;
	// アニメーション情報が保持されているか
	bool m_hasAnimation = false;
};

}  // namespace base
}  // namespace mslib