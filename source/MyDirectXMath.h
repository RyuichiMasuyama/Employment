#pragma once

#define PI 3.141592653589793f

//���ݖ��쐬
//Matrix.h�@Qotanion.h	Vector.h	�����\��
#include "./Math/Vector.h"
#include "./Math/Matrix.h"
#include "./Math/Quaternion.h"

//�e��v�Z�ɂ�����w���p�[�֐��̑��ݗ\��
// 3���_��UV�l����w����W�ł�U���iTangent�j�y��V���iBinormal�j���Z�o
//
// p0, p1, p2    : ���[�J����Ԃł̒��_���W�i�|���S���`�揇�ɂ��邱�Ɓj
// uv0, uv1, uv2 : �e���_��UV���W
// outTangent    : U���iTangent�j�o��
// outBinormal   : V���iBinormal�j�o��

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