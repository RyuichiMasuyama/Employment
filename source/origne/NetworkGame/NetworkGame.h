#pragma once

#include <core/Object/object.h>
#include <core/Network/Network.h>
#include <core/Thread/Thread.h>
#include <queue>

#include <ImGui/imgui.h>

namespace mslib {
namespace networkgame {
class NetworkGameGameObejct :public object::GameObject {
	BASE_CLASS_IS(object::GameObject)

	static constexpr const unsigned char CLIENT = 1;
	static constexpr const unsigned char SERVER = 2;
	static constexpr const unsigned char NON_SEVER_CLIENT = 0;

	static constexpr const char* VOID_UPDATE = "VoidUpdate";
	static constexpr const char* SERVER_UPDATE = "ServerUpdate";
	static constexpr const char* SERVER_BIND_UPDATE = "ServerBindUpdate";
	static constexpr const char* CLIENT_CONNECT_UPDATE = "ClientConnectUpdate";
	static constexpr const char* CLIENT_GAME_UPDATE = "ClientGameUpdate";
public:
	NetworkGameGameObejct() = default;
	~NetworkGameGameObejct();

	void Initialize()override;

	void ImGuiDraw()override {
		switch (m_determineFlag) {
		case NON_SEVER_CLIENT: {
			// �A�b�v�f�[�g�t���O��ύX
			static bool server = false;
			static bool client = false;

			if (ImGui::RadioButton("Server", false)) m_determineFlag = SERVER;
			if (ImGui::RadioButton("Client", false)) m_determineFlag = CLIENT;

			break;
		}
		case CLIENT: {
			// Client���ŃA�h���X�ƃ|�[�g�ԍ���ݒ�
			static char port[256];
			static char address[256];

			static bool connect = false;

			ImGui::InputText("PortNumber", port, 256);
			ImGui::InputText("AddressNumber", address, 256);

			if (ImGui::RadioButton("Connect", false)) m_connetBindFlag = true;

			// �ݒ�
			m_portString = port;
			m_addressString = address;

			break;
		}
		case SERVER: {
			// Server���ŃA�h���X�ƃ|�[�g�ԍ���ݒ�
			static char port[256];
			static char address[256];

			static bool connect = false;

			ImGui::InputText("PortNumber", port, 256);
			ImGui::InputText("AddressNumber", address, 256);

			if (ImGui::RadioButton("Bind", false)) m_connetBindFlag = true;

			// �ݒ�
			m_portString = port;
			m_addressString = address;

			break;
		}
		}

	};

	// void�A�b�v�f�[�g
	void VoidUpdate();
	// Server�̃|�[�g����
	void ServerBindUpdate();
	// Server���̃A�b�v�f�[�g
	void ServerUpdate();
	// Client���ŃT�[�o�[�ɃA�N�Z�X����A�b�v�f�[�g
	void ClientConnectUpdate();
	// Client���ŃQ�[���̃A�b�v�f�[�g
	void ClientGameUpdate();
private:
	// �v���ꗗ
	enum Requirements{
		CONNECT,	// �ڑ��v��
		DATA,		// �f�[�^�v��
		FINISH		// �I���v��
	};
	
	// ���M�f�[�^�̃I�u�W�F�N�g
	struct SendObject {
		Requirements m_requirements;	// �v��
		float m_deltaTime;				// �o�ߎ���
		char m_key;						// �L�[����
	};

	// ���M�p�f�[�^
	network::BaseSendDataObject<SendObject> m_sendObject;

	// ��M�f�[�^�̃X�^�b�N
	std::queue<SendObject> m_queueReceiveObject;

	// Network�N���X
	// Singleton�ɂ���ׂ����H�H
	network::Network m_network;

	// �l�b�g���[�N�Ɏg��Thread
	thread::Thread m_thread;

	// socket
	network::Socket m_socket;

	// address
	network::Address m_address;

	// Client��Server�̃t���O
	unsigned char m_determineFlag;

	// bind��connect�̃t���O
	bool m_connetBindFlag;

	// Address��string
	std::string m_addressString;

	// Port��string
	std::string m_portString;
};
}
}