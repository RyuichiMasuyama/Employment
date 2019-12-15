#include "Input.h"

namespace mslib {
namespace input {

directx::DirectXInput InputDirectXConnect::dxInput;

InputDirectXConnect::InputDirectXConnect(HINSTANCE _hIncetance) {
	dxInput.Init(_hIncetance);
}

bool InputDirectXConnect::GetKeyEnter(unsigned int _key) {
	return dxInput.GetKeyEnter(_key);
}

bool InputDirectXConnect::GetKeyExit(unsigned int _key) {
	return dxInput.GetKeyExit(_key);
}

bool InputDirectXConnect::GetKeyStay(unsigned int _key) {
	return dxInput.GetKeyStay(_key);
}

void InputDirectXConnect::Update() {
	dxInput.Update();
}

Input::Input(HINSTANCE _hIncetance) :InputDirectXConnect(_hIncetance){
}

}
}
