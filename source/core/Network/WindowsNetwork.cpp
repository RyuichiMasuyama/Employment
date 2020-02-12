#include "WindowsNetwork.h"

#pragma warning(disable:4996)

namespace mslib {
namespace network {
namespace windows {
WindowsNetwork::~WindowsNetwork() {
	WSACleanup();
}

void WindowsNetwork::Initialize() {
	WSADATA		m_wd;						// �v�r�`�r�s�`�q�s�t�o�p
	WORD		requiredversion;			// 
	int			sts;						// �߂�l
	int			errcode;					// �\�P�b�g�̃G���[�R�[�h
							// ���̃v���O�������v������o�[�W����
	requiredversion = MAKEWORD(2, 2);

	// �v�h�m�r�n�b�j������
	sts = WSAStartup(MAKEWORD(2, 2), &m_wd);
	if (sts == SOCKET_ERROR)
	{
		errcode = WSAGetLastError();
		errcom(errcode);
		return;
	}

	// �o�[�W�����`�F�b�N
	if (m_wd.wVersion != requiredversion)
	{
		MessageBox(NULL, "VERSION ERROR!", "", MB_OK);
		return ;
	}

	return ;

}

bool WindowsNetwork::Bind(BaseSocket * m_socket, BaseAddress * m_address) {
	// �\�P�b�g���R�s�[
	auto socket = *(SOCKET*)m_socket->GetSocket();

	// �����̃\�P�b�g��IP�A�h���X�A�|�[�g�ԍ������蓖�Ă� NIC����������ꍇ��IP�A�h���X��NIC�w��ɂȂ�B
	if (bind(socket, (sockaddr*)m_address->GetAddress(), sizeof(sockaddr)) == SOCKET_ERROR) {
		errcom(WSAGetLastError());
		return false;
	}

	return true;
}

bool WindowsNetwork::Connect(BaseSocket*m_socket, BaseAddress*m_address) {
	// �\�P�b�g���R�s�[
	auto socket = *static_cast<SOCKET*>(m_socket->GetSocket());

	//�G�R�[�T�[�o�ւ̐ڑ����m��
	if (connect(socket, (sockaddr*)m_address->GetAddress(), sizeof(sockaddr)) < 0) {
		ErrorLog();
		return false;
	}
	return true;
}

unsigned int WindowsNetwork::Send(const char * _sendData, unsigned int _dataSize, BaseSocket * _socket) {
	char encData[RECV_BYFFER_MAX];

	// ���M����������
	int sts;
	
	sts = sendto(
		*static_cast<SOCKET*>(_socket->GetSocket()),	// socket
		encData,										// ���M�f�[�^
		_dataSize,										// �f�[�^�T�C�Y
		0,												// �Ӗ��������ĂȂ�
		nullptr,										// address�̎󂯎��
		sizeof(sockaddr)								// �󂯎�莞�̃T�C�Y
	);

	return sts;
}

unsigned int WindowsNetwork::Receive(char * _reciveData, unsigned int _dataSize, BaseSocket * _socket, BaseAddress* _address) {
	int addr_len = sizeof(sockaddr);

	auto socket = *static_cast<SOCKET*>(_socket->GetSocket());
	auto address = static_cast<sockaddr*>(_address->GetAddress());

	int err;
	int sts = recvfrom(socket,					// �\�P�b�g�ԍ�
		_reciveData,					// ��M�o�b�t�@
		_dataSize,					// ��M�o�b�t�@�o�C�g��
		0,
		address,					// ���M���A�h���X
		&addr_len);					// ��T�����̃o�C�g�����Z�b�g

	if (sts == SOCKET_ERROR)
	{
		err = WSAGetLastError();

		if (err != WSAEINTR)
		{
			errcom(err);
			return SOCKET_ERROR;
		}
	}
	
	return sts;
}

WindowsSocket::WindowsSocket() {
	m_winSocket = INVALID_SOCKET;
}

WindowsSocket::~WindowsSocket() {
	CloseSocket();
}

bool WindowsSocket::CreateUDPSocket() {
	// �\�P�b�g�����łɐ�������Ă���̂�
	// false��Ԃ�
	if (!m_winSocket)return false;

	m_winSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	
	if (m_winSocket == INVALID_SOCKET) {
		auto err = WSAGetLastError();
		errcom(err);
		return false;
	}
	// �\�P�b�g���������������̂�
	// empty�ł͖����Ȃ�
	m_emptyFlag = false;

	return true;
}

bool WindowsSocket::CreateTCPSocket() {
	// �J���\��
	return false;
}

void WindowsSocket::CloseSocket() {
	if (m_winSocket!= INVALID_SOCKET)
	{
		closesocket(m_winSocket);
		m_winSocket = INVALID_SOCKET;
	}
}

void * WindowsSocket::GetSocket() {
	// empty�Ȃ�nullptr��Ԃ�
	if (m_emptyFlag)return nullptr;
	// ����̂Ń|�C���^��Ԃ�
	return static_cast<void*>(&m_winSocket);
}

WindowsAddress::WindowsAddress() {
	// ������
	ZeroMemory(&m_winAddress, sizeof(m_winAddress));
}

void* WindowsAddress::GetAddress() {
	return static_cast<void*>(&m_winAddress);
}

bool WindowsAddress::CreateAddress(std::string _portStr, std::string _addressStr) {
	// �|�[�g�ԍ��𐔗�
	int portno = atoi(_portStr.c_str());

	// ���[�J���A�h���X�\���̂𐶐�
	m_winAddress.sin_family = AF_INET;						//�C���^�[�l�b�g�A�h���X�t�@�~��
	m_winAddress.sin_addr.S_un.S_addr = inet_addr(_addressStr.c_str());	//���C���h�J�[�h���g�p
	m_winAddress.sin_port = htons(portno);			//���[�J���|�[�g		
	
	// ���̂܂܂���100����������
	return true;
}

}
}
}