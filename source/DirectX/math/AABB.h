#pragma once

#include "../../Math/Vector.h"

namespace math {
class AABB {
public:
	AABB() { min = max = Vector3(0.f, 0.f, 0.f); }

	void SetAABB(Vector3 _size, Vector3 _pos) {
		center = min = max = _pos;
		min -= _size;
		max += _size;
	}

	math::Vector3 min, max, center;
};
}