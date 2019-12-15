#pragma once

#ifdef DIRECTX11
#include "./DirectX/DirectInput/DirectXInput.h"
#endif

#include <Singleton.h>

namespace mslib {
namespace input {

#ifdef DIRECTX11
class InputDirectXConnect {
public:
	InputDirectXConnect(HINSTANCE _hIncetance) ;
	InputDirectXConnect() = default;

	~InputDirectXConnect() = default;

	static bool GetKeyEnter(unsigned int _key);
	static bool GetKeyExit(unsigned int _key);
	static bool GetKeyStay(unsigned int _key);

	void Update();
protected:
	static directx::DirectXInput dxInput;
};
#endif

class Input:public InputDirectXConnect {
public:
	Input(HINSTANCE _hIncetance);
	Input() = default;
	~Input() = default;
};
}
}