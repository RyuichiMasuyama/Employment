#include "Network.h"
#include "WindowsNetwork.h"

namespace mslib {
namespace network {
Network::Network() {
	m_basesNetwork = std::make_unique<BasesNetwork>();
}

void Network::Initialize() {
	m_basesNetwork->Initialize();
}

bool Network::Bind(Socket * _socket, Address * _address) {
	return m_basesNetwork->Bind(_socket->GetSocket(), _address->GetAddress());
}

bool Network::Connect(Socket*_socket, Address*_address) {
	return m_basesNetwork->Connect(_socket->GetSocket(), _address->GetAddress());
}

void Network::Send(const char * _sendData, unsigned int _dataSize, Socket * _socket) {
	m_basesNetwork->Send(_sendData, _dataSize, _socket->GetSocket());
}

unsigned int Network::Receive(char * _reciveData, unsigned int _dataSize, Socket * _socket, Address* _address) {
	
	return m_basesNetwork->Receive(_reciveData, _dataSize, _socket->GetSocket(), _address->GetAddress());
}

Socket::Socket() {
	m_winSocket = std::make_unique<BasesSocket>();
}

Address::Address() {
	m_winAddress = std::make_unique<BasesAddress>();
}

}
}
