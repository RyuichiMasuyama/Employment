#pragma once

#include <string>
#include <memory>
#include "./BaseMesh.h"

namespace mslib {
namespace render {

// ���b�V�����_���Ȃǂ�ێ�
class Mesh {
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	Mesh();
	~Mesh() = default;

	// ���b�V��Data�̃��[�h
	void Load(const std::vector<render::PolygonAnimationVertex>& _vecVer, const std::vector<render::PolygonIndex> _vecIndex);

	// �`��
	// �eAPI�ɂ���ĕύX�����
	void Draw();

private:
	// ���Œ��p�N���X�B��
	std::unique_ptr< base::BaseMesh > m_basisMeshPtr;
};

}  // namespace render
}  // namespace mslib