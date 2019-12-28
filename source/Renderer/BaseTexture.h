#pragma once
#include <string>

namespace mslib {
namespace base {
// テクスチャの基底クラス
// base<T>クラスを作って継承させてやるべきかな…
class BaseTexture {
public:
	BaseTexture() = default;
	~BaseTexture() = default;

	virtual bool Load(std::string _fileName) = 0;
	virtual void Send(unsigned int _number) = 0;
};
}
}