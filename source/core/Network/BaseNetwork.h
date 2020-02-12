#pragma once

#include <string>

// ネットワークの基底クラス
namespace mslib {
namespace network {

class BaseSocket;
class BaseAddress;
class BaseNetwork;

// 通信オブジェクト
// Templateで他の型に変換する
template<typename T>
class BaseSendDataObject {
public:
	// データのサイズ
	const unsigned int dataSize = sizeof(T);

	// データ
	union {
		T m_sendObject;
		char m_bitObject[sizeof(T)];
	}data;
};

// Socket
// 自身のIPアドレスと何らかの証明アドレスを入れておく？？
class BaseSocket {
public:
	BaseSocket();

	// UDPソケットの生成
	virtual bool CreateUDPSocket() = 0;

	// TCPソケットの生成
	virtual bool CreateTCPSocket() = 0;

	// ソケットのクローズ
	virtual void CloseSocket() = 0;

	// ソケットを取得する
	// 外部で使わないのでfrined化したほうがいいかも
	virtual void* GetSocket() = 0;

	// 空ならtrueが返ってくる
	bool IsEmpty();
protected:
	bool m_emptyFlag;
};

// Address
class BaseAddress {
public:
	BaseAddress() = default;
	~BaseAddress() = default;

	// アドレスの取得
	// 外部の出さなくてもいいからfriendにしたほうがいいかな
	virtual void* GetAddress() = 0;

	virtual bool CreateAddress(std::string _portStr, std::string _addressStr) = 0;
private:
};

class BaseNetwork {
public:
	// 一度の送信で送信できるデータ
	static constexpr const unsigned int RECV_BYFFER_MAX = 512;

	// 初期化
	virtual void Initialize() = 0;
	
	// 通信確立
	virtual bool Connect(BaseSocket*m_socket, BaseAddress*m_address) = 0;
	
	// アドレスとソケットを関連付ける
	virtual bool Bind(BaseSocket*m_socket, BaseAddress*m_address) = 0;

	// データ送信
	virtual unsigned int Send(const char*_sendData,unsigned int _dataSize, BaseSocket* _socket) = 0;
	// データ受信
	// 返り値:受信バイト数
	virtual unsigned int Receive(char*_reciveData, unsigned int _dataSize, BaseSocket* _socket, BaseAddress * _address) = 0;
private:
	// none
};
}
}