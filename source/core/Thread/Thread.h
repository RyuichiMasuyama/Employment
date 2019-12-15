#pragma once

#include <mutex>
#include <thread>
#include <condition_variable>

namespace mslib {
namespace thread {
class Thread {
public:
	Thread(unsigned int _mask = UINT_MAX);
	~Thread() = default;

	bool IsEmpty() { return m_emptyFlag; };

	template<class T>
	void Push(T _functuin) {
		//m_thread = function;
		m_emptyFlag = false;
	}

private:
	std::condition_variable m_condition;
	std::thread m_thread;
	std::mutex m_mutex;
	std::function<void(void)> m_function;
	bool m_emptyFlag;
};
}
}