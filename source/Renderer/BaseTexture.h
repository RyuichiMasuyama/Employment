#pragma once
#include <string>

namespace mslib {
namespace base {
// �e�N�X�`���̊��N���X
// base<T>�N���X������Čp�������Ă��ׂ����ȁc
class BaseTexture {
public:
	BaseTexture() = default;
	~BaseTexture() = default;

	virtual bool Load(std::string _fileName) = 0;
	virtual void Send(unsigned int _number) = 0;
};
}
}