#include "./MyDirectXMath.h"
#include <stdlib.h>
#include <DirectXMath.h>
#include <memory>

void CalcTangentAndBinormal(
	const math::Vector3 & p0, const math::Vector2 & uv0,
	const math::Vector3 & p1, const math::Vector2 & uv1,
	const math::Vector3 & p2, const math::Vector2 & uv2,
	math::Vector3 & outTangent, math::Vector3 & outBinormal
)
{
	// 5次元→3次元頂点に
	math::Vector3 CP0[3] = {
		math::Vector3(p0.x, uv0.x, uv0.y),
		math::Vector3(p0.y, uv0.x, uv0.y),
		math::Vector3(p0.z, uv0.x, uv0.y),
	};
	math::Vector3 CP1[3] = {
		math::Vector3(p1.x, uv1.x, uv1.y),
		math::Vector3(p1.y, uv1.x, uv1.y),
		math::Vector3(p1.z, uv1.x, uv1.y),
	};
	math::Vector3 CP2[3] = {
		math::Vector3(p2.x, uv2.x, uv2.y),
		math::Vector3(p2.y, uv2.x, uv2.y),
		math::Vector3(p2.z, uv2.x, uv2.y),
	};

	// 平面パラメータからUV軸座標算出
	float U[3], V[3];
	for (int i = 0; i < 3; ++i) {
		math::Vector3 V1 = CP1[i] - CP0[i];
		math::Vector3 V2 = CP2[i] - CP1[i];
		math::Vector3 ABC;

		ABC = math::Vector3::Cross(V1, V2);

		if (ABC.x == 0.0f) {
			// ポリゴンかUV上のポリゴンが縮退してます！
			// _ASSERT(0);
			memset(&outTangent, 0, sizeof(math::Vector3));
			memset(&outBinormal, 0, sizeof(math::Vector3));
			return;
		}
		U[i] = -ABC.y / ABC.x;
		V[i] = -ABC.z / ABC.x;
	}

	memcpy(&outTangent, U, sizeof(float) * 3);
	memcpy(&outBinormal, V, sizeof(float) * 3);

	// 正規化します
	outTangent = outTangent.GetNormal();
	outBinormal = outBinormal.GetNormal();
}
