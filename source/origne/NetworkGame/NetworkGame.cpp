#include "NetworkGame.h"
#include <ImGui/imgui.h>

namespace mslib {
namespace networkgame {
NetworkGameGameObejct::~NetworkGameGameObejct() {
	m_thread.Finish();
}
void NetworkGameGameObejct::Initialize() {
	base::Initialize();

	// �t���Ovoid��
	m_determineFlag = NON_SEVER_CLIENT;

	// ������
	m_network.Initialize();

	// �\�P�b�g�𐶐�
	// m_socket.CreateUDPSocket();

	// m_address.CreateAddress();
	// m_network.Bind();

	// �X���b�h�ɓ����Function��������

	m_connetBindFlag = false;

	// �A�b�v�f�[�gFunction��ǉ�
	CreateUpdateFunction(VOID_UPDATE, &NetworkGameGameObejct::VoidUpdate, this);
	CreateUpdateFunction(SERVER_UPDATE, &NetworkGameGameObejct::ServerUpdate, this);
	CreateUpdateFunction(SERVER_BIND_UPDATE, &NetworkGameGameObejct::ServerBindUpdate, this);
	CreateUpdateFunction(CLIENT_CONNECT_UPDATE, &NetworkGameGameObejct::ClientConnectUpdate, this);
	CreateUpdateFunction(CLIENT_GAME_UPDATE, &NetworkGameGameObejct::ClientGameUpdate, this);

	// �ŏ��̃A�b�v�f�[�g��ݒ�
	SetUpdateFunction(VOID_UPDATE);
}

void NetworkGameGameObejct::VoidUpdate() {
	// void
	// imgui�ŃT�[�o�[���N���C�A���g����ݒ肷��
	switch (m_determineFlag) {
	case NON_SEVER_CLIENT:
		break;

	case CLIENT:
		// Client
		SetUpdateFunction(CLIENT_CONNECT_UPDATE);
		break;

	case SERVER:
		// Server
		SetUpdateFunction(SERVER_BIND_UPDATE);
		break;
	}
}

void NetworkGameGameObejct::ServerBindUpdate() {
	if (m_connetBindFlag) {
		// �o�C���h������A�b�v�f�[�g�ύX
		SetUpdateFunction(SERVER_UPDATE);

		// �\�P�b�g�ƃA�h���X����
		m_address.CreateAddress(m_portString, m_addressString);
		m_socket.CreateUDPSocket();	
		
		// �o�C���h
		m_network.Bind(&m_socket, &m_address);

		// �G�R�[�T�[�o�[��Thread
		m_thread.Push([&]() {
			// �󂯎��p�I�u�W�F�N�g
			network::BaseSendDataObject<SendObject> m_receiveObject;

			// �󂯎��
			m_network.Receive(m_receiveObject.data.m_bitObject, m_receiveObject.dataSize, &m_socket, &m_address);

			// ���߂�
			m_queueReceiveObject.push(m_receiveObject.data.m_sendObject);
		});
	}
}

void NetworkGameGameObejct::ServerUpdate() {
}

void NetworkGameGameObejct::ClientConnectUpdate() {
	if (m_connetBindFlag) {
		// �R�l�N�g������A�b�v�f�[�g�ύX
		SetUpdateFunction(CLIENT_GAME_UPDATE);

		// �\�P�b�g�ƃA�h���X����
		m_address.CreateAddress(m_portString, m_addressString);
		m_socket.CreateUDPSocket();

		// �R�l�N�g
		m_network.Connect(&m_socket, &m_address);

		// �󂯎��݂̂�Thread
		m_thread.Push([&]() {
			// �󂯎��p�I�u�W�F�N�g
			network::BaseSendDataObject<SendObject> m_receiveObject;

			// �󂯎��
			m_network.Receive(m_receiveObject.data.m_bitObject, m_receiveObject.dataSize, &m_socket, &m_address);

			// ���߂�
			m_queueReceiveObject.push(m_receiveObject.data.m_sendObject);
		});
	}
}

void NetworkGameGameObejct::ClientGameUpdate() {
}

}
}