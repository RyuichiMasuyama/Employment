#include "NetworkGame.h"
#include <ImGui/imgui.h>

namespace mslib {
namespace networkgame {
NetworkGameGameObejct::~NetworkGameGameObejct() {
	m_thread.Finish();
}
void NetworkGameGameObejct::Initialize() {
	base::Initialize();

	// フラグvoidに
	m_determineFlag = NON_SEVER_CLIENT;

	// 初期化
	m_network.Initialize();

	// ソケットを生成
	// m_socket.CreateUDPSocket();

	// m_address.CreateAddress();
	// m_network.Bind();

	// スレッドに入れるFunctionを代入する

	m_connetBindFlag = false;

	// アップデートFunctionを追加
	CreateUpdateFunction(VOID_UPDATE, &NetworkGameGameObejct::VoidUpdate, this);
	CreateUpdateFunction(SERVER_UPDATE, &NetworkGameGameObejct::ServerUpdate, this);
	CreateUpdateFunction(SERVER_BIND_UPDATE, &NetworkGameGameObejct::ServerBindUpdate, this);
	CreateUpdateFunction(CLIENT_CONNECT_UPDATE, &NetworkGameGameObejct::ClientConnectUpdate, this);
	CreateUpdateFunction(CLIENT_GAME_UPDATE, &NetworkGameGameObejct::ClientGameUpdate, this);

	// 最初のアップデートを設定
	SetUpdateFunction(VOID_UPDATE);
}

void NetworkGameGameObejct::VoidUpdate() {
	// void
	// imguiでサーバーかクライアントかを設定する
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
		// バインドした後アップデート変更
		SetUpdateFunction(SERVER_UPDATE);

		// ソケットとアドレス生成
		m_address.CreateAddress(m_portString, m_addressString);
		m_socket.CreateUDPSocket();	
		
		// バインド
		m_network.Bind(&m_socket, &m_address);

		// エコーサーバーのThread
		m_thread.Push([&]() {
			// 受け取り用オブジェクト
			network::BaseSendDataObject<SendObject> m_receiveObject;

			// 受け取る
			m_network.Receive(m_receiveObject.data.m_bitObject, m_receiveObject.dataSize, &m_socket, &m_address);

			// 貯める
			m_queueReceiveObject.push(m_receiveObject.data.m_sendObject);
		});
	}
}

void NetworkGameGameObejct::ServerUpdate() {
}

void NetworkGameGameObejct::ClientConnectUpdate() {
	if (m_connetBindFlag) {
		// コネクトした後アップデート変更
		SetUpdateFunction(CLIENT_GAME_UPDATE);

		// ソケットとアドレス生成
		m_address.CreateAddress(m_portString, m_addressString);
		m_socket.CreateUDPSocket();

		// コネクト
		m_network.Connect(&m_socket, &m_address);

		// 受け取りのみのThread
		m_thread.Push([&]() {
			// 受け取り用オブジェクト
			network::BaseSendDataObject<SendObject> m_receiveObject;

			// 受け取る
			m_network.Receive(m_receiveObject.data.m_bitObject, m_receiveObject.dataSize, &m_socket, &m_address);

			// 貯める
			m_queueReceiveObject.push(m_receiveObject.data.m_sendObject);
		});
	}
}

void NetworkGameGameObejct::ClientGameUpdate() {
}

}
}