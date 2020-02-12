#pragma once

#define PI 3.141592653589793f

//現在未作成
//Matrix.h　Qotanion.h	Vector.h	統合予定
#include "./Math/Vector.h"
#include "./Math/Matrix.h"
#include "./Math/Quaternion.h"

//各種計算におけるヘルパー関数の増設予定
// 3頂点とUV値から指定座標でのU軸（Tangent）及びV軸（Binormal）を算出
//
// p0, p1, p2    : ローカル空間での頂点座標（ポリゴン描画順にすること）
// uv0, uv1, uv2 : 各頂点のUV座標
// outTangent    : U軸（Tangent）出力
// outBinormal   : V軸（Binormal）出力

void CalcTangentAndBinormal(
	const math::Vector3 & p0, const math::Vector2 & uv0,
	const math::Vector3 & p1, const math::Vector2 & uv1,
	const math::Vector3 & p2, const math::Vector2 & uv2,
	math::Vector3 & outTangent, math::Vector3 & outBinormal
);

namespace math {
inline float ToRadian(float _base) {
	return _base * PI / 180.f;
}
inline float ToDegrees(float _base) {
	return _base * 180.f / PI;
}
}