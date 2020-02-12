#pragma once

#include <memory>
#include <string>
#include <Singleton.h>
#include "BaseNetwork.h"

// �ʐM
// �B��
namespace mslib {
namespace network {
;
;
// �\�P�b�g
class Socket {
public:
	Socket();
	~Socket() = default;

	// UDP�\�P�b�g�̐���
	virtual bool CreateUDPSocket() { return m_winSocket->CreateUDPSocket(); };

	// TCP�\�P�b�g�̐���
	virtual bool CreateTCPSocket() { return m_winSocket->CreateTCPSocket(); };

	// �\�P�b�g�̃N���[�Y
	virtual void CloseSocket() { m_winSocket->CloseSocket(); };

	// �\�P�b�g���擾����
	// �O���Ŏg��Ȃ��̂�frined�������ق�����������
	virtual BaseSocket* GetSocket() { return m_winSocket.get(); };

	// ��Ȃ�true���Ԃ��Ă���
	bool IsEmpty() { return m_winSocket->IsEmpty(); };
private:
	std::unique_ptr<BaseSocket> m_winSocket;
};

// �A�h���X
class Address {
public:
	Address();
	~Address() = default;

	// �A�h���X�̎擾
	// �O���̏o���Ȃ��Ă���������friend�ɂ����ق�����������
	BaseAddress* GetAddress() { return m_winAddress.get(); };

	bool CreateAddress(std::string _portStr, std::string _addressStr) { return m_winAddress->CreateAddress(_portStr, _addressStr); };
private:
	std::unique_ptr<BaseAddress> m_winAddress;
};

class Network {
public:
	Network();
	~Network() = default;

	// �Z�b�g�A�b�v
	void Initialize();

	// �o�C���h
	bool Bind(Socket*_socket, Address*_address);
	
	// �R�l�N�g
	bool Connect(Socket*_socket, Address*_address);
	
	// ���M
	void Send(const char*_sendData, unsigned int _dataSize, Socket* _socket);
	
	// ��M
	unsigned int Receive(char*_reciveData, unsigned int _dataSize, Socket* _socket, Address* _address);
private:
	std::unique_ptr < BaseNetwork > m_basesNetwork;
};
}
}