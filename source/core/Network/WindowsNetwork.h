#pragma once

// Windows�g�p��
// Winsock���g�p����
// �l�b�g���[�N���m������
#ifdef WINDOWS

#include "wsock32error.h"

#include "./BaseNetwork.h"

namespace mslib {
namespace network {
namespace windows {

class WindowsSocket :public BaseSocket{
public:
	WindowsSocket();
	~WindowsSocket();

	bool CreateUDPSocket()override;

	bool CreateTCPSocket()override;

	void CloseSocket()override;

	void* GetSocket()override;
private:
	SOCKET m_winSocket;
};

class WindowsAddress :public BaseAddress {
public:
	// �l�̏�����
	WindowsAddress();
	~WindowsAddress() = default;

	// �A�h���X�̐���
	bool CreateAddress(std::string _portStr, std::string _addressStr) override;

	// �A�h���X�̎擾
	void* GetAddress()override;
private:
	sockaddr_in m_winAddress;
};

class WindowsNetwork :public BaseNetwork {
public:
	WindowsNetwork() = default;
	~WindowsNetwork();

	// ������
	void Initialize()override;
	
	// �o�C���h
	bool Bind(BaseSocket*m_socket, BaseAddress*m_address)override;

	// �R�l�N�g
	bool Connect(BaseSocket*m_socket, BaseAddress*m_address)override;

	// �f�[�^���M�E�Ԃ�l���M�ł����f�[�^��
	unsigned int Send(const char*_sendData, unsigned int _dataSize, BaseSocket* _socket)override;
	// �f�[�^��M�E�Ԃ�l��M�����f�[�^��
	unsigned int Receive(char*_reciveData, unsigned int _dataSize, BaseSocket* _socket, BaseAddress* _address)override;
private:
};
}
// ���N���X�B��
using BasesNetwork = windows::WindowsNetwork;
using BasesSocket = windows::WindowsSocket;
using BasesAddress = windows::WindowsAddress;
}
}
#endif // WINDOWS