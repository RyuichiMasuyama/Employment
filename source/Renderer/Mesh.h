#pragma once

#include <string>
#include <memory>
#include "./BaseMesh.h"

namespace mslib {
namespace render {

// ���b�V�����_���Ȃǂ�ێ�
class Mesh {
public:
	Mesh();
	~Mesh() = default;

	void Draw();

private:
	// ���Œ��p�N���X�B��
	std::unique_ptr< base::BaseMesh > m_basisMeshPtr;
};

}  // namespace render
}  // namespace mslib