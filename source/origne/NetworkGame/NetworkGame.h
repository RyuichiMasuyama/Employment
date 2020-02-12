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
			// アップデートフラグを変更
			static bool server = false;
			static bool client = false;

			if (ImGui::RadioButton("Server", false)) m_determineFlag = SERVER;
			if (ImGui::RadioButton("Client", false)) m_determineFlag = CLIENT;

			break;
		}
		case CLIENT: {
			// Client側でアドレスとポート番号を設定
			static char port[256];
			static char address[256];

			static bool connect = false;

			ImGui::InputText("PortNumber", port, 256);
			ImGui::InputText("AddressNumber", address, 256);

			if (ImGui::RadioButton("Connect", false)) m_connetBindFlag = true;

			// 設定
			m_portString = port;
			m_addressString = address;

			break;
		}
		case SERVER: {
			// Server側でアドレスとポート番号を設定
			static char port[256];
			static char address[256];

			static bool connect = false;

			ImGui::InputText("PortNumber", port, 256);
			ImGui::InputText("AddressNumber", address, 256);

			if (ImGui::RadioButton("Bind", false)) m_connetBindFlag = true;

			// 設定
			m_portString = port;
			m_addressString = address;

			break;
		}
		}

	};

	// voidアップデート
	void VoidUpdate();
	// Serverのポート生成
	void ServerBindUpdate();
	// Server側のアップデート
	void ServerUpdate();
	// Client側でサーバーにアクセスするアップデート
	void ClientConnectUpdate();
	// Client側でゲームのアップデート
	void ClientGameUpdate();
private:
	// 要求一覧
	enum Requirements{
		CONNECT,	// 接続要求
		DATA,		// データ要求
		FINISH		// 終了要求
	};
	
	// 送信データのオブジェクト
	struct SendObject {
		Requirements m_requirements;	// 要求
		float m_deltaTime;				// 経過時間
		char m_key;						// キー入力
	};

	// 送信用データ
	network::BaseSendDataObject<SendObject> m_sendObject;

	// 受信データのスタック
	std::queue<SendObject> m_queueReceiveObject;

	// Networkクラス
	// Singletonにするべきか？？
	network::Network m_network;

	// ネットワークに使うThread
	thread::Thread m_thread;

	// socket
	network::Socket m_socket;

	// address
	network::Address m_address;

	// ClientかServerのフラグ
	unsigned char m_determineFlag;

	// bindとconnectのフラグ
	bool m_connetBindFlag;

	// Addressのstring
	std::string m_addressString;

	// Portのstring
	std::string m_portString;
};
}
}