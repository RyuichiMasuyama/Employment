#pragma once

// Windows使用時
// Winsockを使用した
// ネットワークを確立する
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
	// 値の初期化
	WindowsAddress();
	~WindowsAddress() = default;

	// アドレスの生成
	bool CreateAddress(std::string _portStr, std::string _addressStr) override;

	// アドレスの取得
	void* GetAddress()override;
private:
	sockaddr_in m_winAddress;
};

class WindowsNetwork :public BaseNetwork {
public:
	WindowsNetwork() = default;
	~WindowsNetwork();

	// 初期化
	void Initialize()override;
	
	// バインド
	bool Bind(BaseSocket*m_socket, BaseAddress*m_address)override;

	// コネクト
	bool Connect(BaseSocket*m_socket, BaseAddress*m_address)override;

	// データ送信・返り値送信できたデータ数
	unsigned int Send(const char*_sendData, unsigned int _dataSize, BaseSocket* _socket)override;
	// データ受信・返り値受信したデータ数
	unsigned int Receive(char*_reciveData, unsigned int _dataSize, BaseSocket* _socket, BaseAddress* _address)override;
private:
};
}
// 基底クラス隠蔽
using BasesNetwork = windows::WindowsNetwork;
using BasesSocket = windows::WindowsSocket;
using BasesAddress = windows::WindowsAddress;
}
}
#endif // WINDOWS