#include "BaseNetwork.h"
namespace mslib {
namespace network {
BaseSocket::BaseSocket() {
	// ���߂͋�Ȃ̂�true
	m_emptyFlag = true;
}
bool BaseSocket::IsEmpty() {
	return m_emptyFlag;
}

}
}

