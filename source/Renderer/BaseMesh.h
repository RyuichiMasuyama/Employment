#pragma once

#include <vector>
#include "../MyDirectXMath.h"

namespace mslib {
namespace render {
// ���_���
struct PolygonVertex {
	math::Vector3 pos;
	math::Vector3 normal;
	math::Vector4 color;
	math::Vector3 tangent;
};

// �A�j���[�V�������_���
struct PolygonAnimationVertex {
	math::Vector3 pos;			// ���_�ʒu
	math::Vector3 normal;		// �@��
	math::Vector2 tex;			// �e�N�X�`��uv
	math::Vector4 color;		// �F
	math::Vector3 tangent;		// �^���W�F���g
	int			  boneIndex[4];	// �E�F�C�g�C���f�b�N�X
	float		  boneWeight[4];// �C���f�b�N�X�ɑΉ������E�F�C�g
	int			  boneNum;		// �{�[����
};

// �C���f�b�N�X
typedef unsigned int PolygonIndex;

// �{�[�����
struct Bone {
	unsigned int idx = -1;			// �{�[���z��̃C���f�b�N�X�ԍ�
	math::Matrix matrix;			// �����z�u�s��
	math::Matrix animationMatrix;	// �{�[���s��
	math::Matrix offsetMatrix;		// �{�[���I�t�Z�b�g�s��
};

}  // namespace render
namespace base {

class BaseMesh {
public:
	BaseMesh() = default;
	~BaseMesh() = default;

	// ���W�n�̈Ⴂ��␳���邽�߁A���[�h�����𕪂���
	virtual bool Load(const std::vector<render::PolygonAnimationVertex>& _vecVer, const std::vector<render::PolygonIndex> _vecIndex) = 0;
	// �A�j���[�V�����̃f�[�^�����[�h����
	// virtual bool AnimationLoad(const std::vector<render::PolygonAnimationVertex>& _vecWight) = 0;
	// �`��R�}���h���镔��
	virtual void Draw() = 0;
protected:
	// �C���f�b�N�X���
	std::vector<render::PolygonIndex> m_index;
	// ���_���
	// std::vector<render::PolygonVertex> m_vertex;
	// �A�j���[�V��������������A�j���[�V�������
	std::vector<render::PolygonAnimationVertex> m_animationWight;
	// �A�j���[�V������񂪕ێ�����Ă��邩
	bool m_hasAnimation = false;
};

}  // namespace base
}  // namespace mslib