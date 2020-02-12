#include "WindowsNetwork.h"

#pragma warning(disable:4996)

namespace mslib {
namespace network {
namespace windows {
WindowsNetwork::~WindowsNetwork() {
	WSACleanup();
}

void WindowsNetwork::Initialize() {
	WSADATA		m_wd;						// ＷＳＡＳＴＡＲＴＵＰ用
	WORD		requiredversion;			// 
	int			sts;						// 戻り値
	int			errcode;					// ソケットのエラーコード
							// このプログラムが要求するバージョン
	requiredversion = MAKEWORD(2, 2);

	// ＷＩＮＳＯＣＫ初期化
	sts = WSAStartup(MAKEWORD(2, 2), &m_wd);
	if (sts == SOCKET_ERROR)
	{
		errcode = WSAGetLastError();
		errcom(errcode);
		return;
	}

	// バージョンチェック
	if (m_wd.wVersion != requiredversion)
	{
		MessageBox(NULL, "VERSION ERROR!", "", MB_OK);
		return ;
	}

	return ;

}

bool WindowsNetwork::Bind(BaseSocket * m_socket, BaseAddress * m_address) {
	// ソケットをコピー
	auto socket = *(SOCKET*)m_socket->GetSocket();

	// 自分のソケットにIPアドレス、ポート番号を割り当てる NICが複数ある場合はIPアドレスがNIC指定になる。
	if (bind(socket, (sockaddr*)m_address->GetAddress(), sizeof(sockaddr)) == SOCKET_ERROR) {
		errcom(WSAGetLastError());
		return false;
	}

	return true;
}

bool WindowsNetwork::Connect(BaseSocket*m_socket, BaseAddress*m_address) {
	// ソケットをコピー
	auto socket = *static_cast<SOCKET*>(m_socket->GetSocket());

	//エコーサーバへの接続を確立
	if (connect(socket, (sockaddr*)m_address->GetAddress(), sizeof(sockaddr)) < 0) {
		ErrorLog();
		return false;
	}
	return true;
}

unsigned int WindowsNetwork::Send(const char * _sendData, unsigned int _dataSize, BaseSocket * _socket) {
	char encData[RECV_BYFFER_MAX];

	// 送信成功文字列数
	int sts;
	
	sts = sendto(
		*static_cast<SOCKET*>(_socket->GetSocket()),	// socket
		encData,										// 送信データ
		_dataSize,										// データサイズ
		0,												// 意味理解してない
		nullptr,										// addressの受け取り
		sizeof(sockaddr)								// 受け取り時のサイズ
	);

	return sts;
}

unsigned int WindowsNetwork::Receive(char * _reciveData, unsigned int _dataSize, BaseSocket * _socket, BaseAddress* _address) {
	int addr_len = sizeof(sockaddr);

	auto socket = *static_cast<SOCKET*>(_socket->GetSocket());
	auto address = static_cast<sockaddr*>(_address->GetAddress());

	int err;
	int sts = recvfrom(socket,					// ソケット番号
		_reciveData,					// 受信バッファ
		_dataSize,					// 受信バッファバイト長
		0,
		address,					// 送信元アドレス
		&addr_len);					// 第５引数のバイト長をセット

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
	// ソケットがすでに生成されているので
	// falseを返す
	if (!m_winSocket)return false;

	m_winSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	
	if (m_winSocket == INVALID_SOCKET) {
		auto err = WSAGetLastError();
		errcom(err);
		return false;
	}
	// ソケット生成が成功したので
	// emptyでは無くなる
	m_emptyFlag = false;

	return true;
}

bool WindowsSocket::CreateTCPSocket() {
	// 開発予定
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
	// emptyならnullptrを返す
	if (m_emptyFlag)return nullptr;
	// あるのでポインタを返す
	return static_cast<void*>(&m_winSocket);
}

WindowsAddress::WindowsAddress() {
	// 初期化
	ZeroMemory(&m_winAddress, sizeof(m_winAddress));
}

void* WindowsAddress::GetAddress() {
	return static_cast<void*>(&m_winAddress);
}

bool WindowsAddress::CreateAddress(std::string _portStr, std::string _addressStr) {
	// ポート番号を数列化
	int portno = atoi(_portStr.c_str());

	// ローカルアドレス構造体を生成
	m_winAddress.sin_family = AF_INET;						//インターネットアドレスファミリ
	m_winAddress.sin_addr.S_un.S_addr = inet_addr(_addressStr.c_str());	//ワイルドカードを使用
	m_winAddress.sin_port = htons(portno);			//ローカルポート		
	
	// 今のままだと100％成功する
	return true;
}

}
}
}