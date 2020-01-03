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
		// �쐬�Ɏ��s
		MessageBox(hwnd, "DirectInput8�̍쐬�Ɏ��s", "", MB_OK);
		return;
	}

	// IDirectInputDevice8�̎擾
	ret = m_dxInput->CreateDevice(GUID_SysKeyboard, &m_dxKeyInoutDevice, NULL);
	if (FAILED(ret)) {
		MessageBox(hwnd, "�L�[�{�[�h�f�o�C�X�̍쐬�Ɏ��s", "", MB_OK);
		m_dxInput->Release();
		return;
	}

	// ���̓f�[�^�`���̃Z�b�g
	ret = m_dxKeyInoutDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(ret)) {
		MessageBox(hwnd, "���̓f�[�^�`���̃Z�b�g���s", "", MB_OK);
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
		// �����L�[���͂������
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
		// �����L�[���͂������
		if (itr & 0x80) {
			anyKey = true;
			break;
		}
	}

	return anyKey;
}

void DirectXInput::Update() {
	// ����J�n
	m_dxKeyInoutDevice->Acquire();
	memcpy(m_key, m_oldKey, sizeof(m_key));
	ZeroMemory(m_key, sizeof(m_key));
	auto ret = m_dxKeyInoutDevice->GetDeviceState(sizeof(m_key), m_key);
	if (FAILED(ret)) {
		// ���s�Ȃ�ĊJ�����Ă�����x�擾
		m_dxKeyInoutDevice->Acquire();
		m_dxKeyInoutDevice->GetDeviceState(sizeof(m_key), m_key);
	}
}

}
}
