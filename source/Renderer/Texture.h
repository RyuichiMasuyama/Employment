#pragma once

#include "./BaseTexture.h"
#include <memory>

namespace mslib {
namespace texture {
class MyTexture {
public:
	MyTexture();
	~MyTexture() = default;

	void Send(int _number);
	void Load(std::string _fileNmae);
private:
	std::unique_ptr<base::BaseTexture> m_baseTexture;
};
}
}