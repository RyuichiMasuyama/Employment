#pragma once

#include <mutex>
#include <thread>
#include <condition_variable>

namespace mslib {
namespace thread {
class Thread {
public:
	Thread(unsigned int _mask = UINT_MAX);
	virtual ~Thread();

	bool IsEmpty() { return m_emptyFlag; };

	void Push(std::function<void(void)> _functuin);
	void Pop();

	void Finish();
private:
	// 制御
	std::condition_variable m_condition;
	std::thread m_thread;
	std::mutex m_mutex;
	
	// 切り替え可能なFuncion
	std::function<void(void)> m_function;

	// Thread内部で動き続けるFunction
	std::function<void(void)> m_threadFunction;

	// 切り替え可能Functionが空か
	bool m_emptyFlag;

	// スレッドを終了させるフラグ
	bool m_threadFinish;
};
}
}