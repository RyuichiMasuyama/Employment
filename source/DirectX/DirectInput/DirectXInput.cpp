#include "DirectXInput.h"

namespace mslib {
namespace directx {
DirectXInput::DirectXInput() {
}

DirectXInput::~DirectXInput() {
	if (m_once)return;
	m_dxKeyInoutDevice->Release();
	m_dxInput->Release();
	m_dxKeyInoutDevice = nullptr;
	m_dxInput = nullptr;
}

void DirectXInput::Init(HINSTANCE _hIncetance) {
	if (!m_once) return;
	m_once = false;
	auto hwnd = GetActiveWindow();
	HRESULT ret = DirectInput8Create(_hIncetance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_dxInput, NULL);
	if (FAILED(ret)) {
		// 作成に失敗
		MessageBox(hwnd, "DirectInput8の作成に失敗", "", MB_OK);
		return;
	}

	// IDirectInputDevice8の取得
	ret = m_dxInput->CreateDevice(GUID_SysKeyboard, &m_dxKeyInoutDevice, NULL);
	if (FAILED(ret)) {
		MessageBox(hwnd, "キーボードデバイスの作成に失敗", "", MB_OK);
		m_dxInput->Release();
		return;
	}

	// 入力データ形式のセット
	ret = m_dxKeyInoutDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(ret)) {
		MessageBox(hwnd, "入力データ形式のセット失敗", "", MB_OK);
		m_dxKeyInoutDevice->Release();
		m_dxInput->Release();
		return;
	}
	for (auto& itr : m_key) {
		itr = 0x00;
	}
	for (auto& itr : m_oldKey) {
		itr = 0x00;
	}
}

bool DirectXInput::GetKeyEnter(unsigned int _key)
{
	return (!(m_oldKey[_key] & 0x80)) && (m_key[_key] & 0x80);
}

bool DirectXInput::GetKeyExit(unsigned int _key)
{
	return (m_oldKey[_key] & 0x80) && !(m_key[_key] & 0x80);
}

bool DirectXInput::GetKeyStay(unsigned int _key)
{
	return m_key[_key] & 0x80;
}

bool DirectXInput::GetAnyEnter() {
	bool anyKey = false;

	for (int i = 0; i < MSK_MAX; i++) {
		// 何かキー入力があれば
		if ((!(m_oldKey[i] & 0x80)) && (m_key[i] & 0x80)) {
			anyKey = true;
			break;
		}
	}
	return anyKey;
}

bool DirectXInput::GetAnyStay() {
	bool anyKey = false;

	for (auto itr : m_key) {
		// 何かキー入力があれば
		if (itr & 0x80) {
			anyKey = true;
			break;
		}
	}

	return anyKey;
}

void DirectXInput::Update() {
	// 動作開始
	m_dxKeyInoutDevice->Acquire();
	memcpy(m_key, m_oldKey, sizeof(m_key));
	ZeroMemory(m_key, sizeof(m_key));
	auto ret = m_dxKeyInoutDevice->GetDeviceState(sizeof(m_key), m_key);
	if (FAILED(ret)) {
		// 失敗なら再開させてもう一度取得
		m_dxKeyInoutDevice->Acquire();
		m_dxKeyInoutDevice->GetDeviceState(sizeof(m_key), m_key);
	}
}

}
}
