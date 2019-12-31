#pragma once

#include "./Math/Vector.h"

namespace mslib {
namespace render {
struct MaterialData {
	math::Vector3 ambient = math::Vector3(0.1f, 0.1f, 0.1f);		//�A���r�G���g
	math::Vector3 diffuse = math::Vector3(0.8f, 0.8f, 0.8f);		//�f�B�t���[�Y
	math::Vector3 emissive = math::Vector3(0.f, 0.f, 0.f);		//�G�~�b�V�u
	math::Vector3 bump = math::Vector3(0.f, 0.f, 1.f);			//�o���v
	float transparency = 0.f;			//�g�����X�y�A�����g
	math::Vector4 specular = math::Vector4(0.2f, 0.2f, 0.2f, 0.9f);		//�X�y�L����(w=Power)
	float shininess = 0.f;			//�V���C�j�[�Y
	float reflectivity = 0.f;			//���t���N�V����
};
}
}