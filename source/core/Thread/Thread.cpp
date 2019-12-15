#include "./Thread.h"
#include "./ThreadAffinity.h"

namespace mslib {
namespace thread {
Thread::Thread(unsigned int _mask) :m_emptyFlag(false) {
	std::function<void(void)> function = [&]() {
		std::unique_lock<std::mutex> lk(m_mutex);

		while (true) {
			m_condition.wait(lk, [&] {return m_emptyFlag; });

			m_function();

			m_emptyFlag = true;
		}
	};
	ThreadAffinity(m_thread.native_handle(), _mask);
}

}
}
