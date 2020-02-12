#include "BaseNetwork.h"
namespace mslib {
namespace network {
BaseSocket::BaseSocket() {
	// ‰‚ß‚Í‹ó‚È‚Ì‚Åtrue
	m_emptyFlag = true;
}
bool BaseSocket::IsEmpty() {
	return m_emptyFlag;
}

}
}

