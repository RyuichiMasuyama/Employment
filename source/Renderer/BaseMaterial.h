#pragma once

#include <string>
#include "./MaterialData.h"

namespace mslib {
namespace render {
class BaseMaterial {
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	BaseMaterial() = default;
	~BaseMaterial() = default;

	// GPU���M
	virtual void Send() = 0;
	// ���[�h
	virtual void Load(std::string _fileName) = 0;

	// ���ۂ�Material�̃f�[�^
	MaterialData materialData;
};
}
}

