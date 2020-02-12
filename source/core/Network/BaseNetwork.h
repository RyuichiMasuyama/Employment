#pragma once

#include <string>

// �l�b�g���[�N�̊��N���X
namespace mslib {
namespace network {

class BaseSocket;
class BaseAddress;
class BaseNetwork;

// �ʐM�I�u�W�F�N�g
// Template�ő��̌^�ɕϊ�����
template<typename T>
class BaseSendDataObject {
public:
	// �f�[�^�̃T�C�Y
	const unsigned int dataSize = sizeof(T);

	// �f�[�^
	union {
		T m_sendObject;
		char m_bitObject[sizeof(T)];
	}data;
};

// Socket
// ���g��IP�A�h���X�Ɖ��炩�̏ؖ��A�h���X�����Ă����H�H
class BaseSocket {
public:
	BaseSocket();

	// UDP�\�P�b�g�̐���
	virtual bool CreateUDPSocket() = 0;

	// TCP�\�P�b�g�̐���
	virtual bool CreateTCPSocket() = 0;

	// �\�P�b�g�̃N���[�Y
	virtual void CloseSocket() = 0;

	// �\�P�b�g���擾����
	// �O���Ŏg��Ȃ��̂�frined�������ق�����������
	virtual void* GetSocket() = 0;

	// ��Ȃ�true���Ԃ��Ă���
	bool IsEmpty();
protected:
	bool m_emptyFlag;
};

// Address
class BaseAddress {
public:
	BaseAddress() = default;
	~BaseAddress() = default;

	// �A�h���X�̎擾
	// �O���̏o���Ȃ��Ă���������friend�ɂ����ق�����������
	virtual void* GetAddress() = 0;

	virtual bool CreateAddress(std::string _portStr, std::string _addressStr) = 0;
private:
};

class BaseNetwork {
public:
	// ��x�̑��M�ő��M�ł���f�[�^
	static constexpr const unsigned int RECV_BYFFER_MAX = 512;

	// ������
	virtual void Initialize() = 0;
	
	// �ʐM�m��
	virtual bool Connect(BaseSocket*m_socket, BaseAddress*m_address) = 0;
	
	// �A�h���X�ƃ\�P�b�g���֘A�t����
	virtual bool Bind(BaseSocket*m_socket, BaseAddress*m_address) = 0;

	// �f�[�^���M
	virtual unsigned int Send(const char*_sendData,unsigned int _dataSize, BaseSocket* _socket) = 0;
	// �f�[�^��M
	// �Ԃ�l:��M�o�C�g��
	virtual unsigned int Receive(char*_reciveData, unsigned int _dataSize, BaseSocket* _socket, BaseAddress * _address) = 0;
private:
	// none
};
}
}