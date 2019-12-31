#pragma once

#include "./Math/Vector.h"

namespace mslib {
namespace render {
struct MaterialData {
	math::Vector3 ambient = math::Vector3(0.1f, 0.1f, 0.1f);		//アンビエント
	math::Vector3 diffuse = math::Vector3(0.8f, 0.8f, 0.8f);		//ディフューズ
	math::Vector3 emissive = math::Vector3(0.f, 0.f, 0.f);		//エミッシブ
	math::Vector3 bump = math::Vector3(0.f, 0.f, 1.f);			//バンプ
	float transparency = 0.f;			//トランスペアレント
	math::Vector4 specular = math::Vector4(0.2f, 0.2f, 0.2f, 0.9f);		//スペキュラ(w=Power)
	float shininess = 0.f;			//シャイニーズ
	float reflectivity = 0.f;			//リフレクション
};
}
}