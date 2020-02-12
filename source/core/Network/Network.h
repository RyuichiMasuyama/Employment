#pragma once

#include <memory>
#include <string>
#include <Singleton.h>
#include "BaseNetwork.h"

// 通信
// 隠蔽
namespace mslib {
namespace network {
;
;
// ソケット
class Socket {
public:
	Socket();
	~Socket() = default;

	// UDPソケットの生成
	virtual bool CreateUDPSocket() { return m_winSocket->CreateUDPSocket(); };

	// TCPソケットの生成
	virtual bool CreateTCPSocket() { return m_winSocket->CreateTCPSocket(); };

	// ソケットのクローズ
	virtual void CloseSocket() { m_winSocket->CloseSocket(); };

	// ソケットを取得する
	// 外部で使わないのでfrined化したほうがいいかも
	virtual BaseSocket* GetSocket() { return m_winSocket.get(); };

	// 空ならtrueが返ってくる
	bool IsEmpty() { return m_winSocket->IsEmpty(); };
private:
	std::unique_ptr<BaseSocket> m_winSocket;
};

// アドレス
class Address {
public:
	Address();
	~Address() = default;

	// アドレスの取得
	// 外部の出さなくてもいいからfriendにしたほうがいいかな
	BaseAddress* GetAddress() { return m_winAddress.get(); };

	bool CreateAddress(std::string _portStr, std::string _addressStr) { return m_winAddress->CreateAddress(_portStr, _addressStr); };
private:
	std::unique_ptr<BaseAddress> m_winAddress;
};

class Network {
public:
	Network();
	~Network() = default;

	// セットアップ
	void Initialize();

	// バインド
	bool Bind(Socket*_socket, Address*_address);
	
	// コネクト
	bool Connect(Socket*_socket, Address*_address);
	
	// 送信
	void Send(const char*_sendData, unsigned int _dataSize, Socket* _socket);
	
	// 受信
	unsigned int Receive(char*_reciveData, unsigned int _dataSize, Socket* _socket, Address* _address);
private:
	std::unique_ptr < BaseNetwork > m_basesNetwork;
};
}
}