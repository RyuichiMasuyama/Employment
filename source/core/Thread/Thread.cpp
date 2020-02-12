#include "./Thread.h"
#include "./ThreadAffinity.h"

namespace mslib {
namespace thread {
Thread::Thread(unsigned int _mask) :m_emptyFlag(true) {
	// スレッドを終了させない
	m_threadFinish = false;

	// 内部で動き続けるFunctionを生成
	m_threadFunction = [&]() {
		std::unique_lock<std::mutex> lk(m_mutex);

		while (!m_threadFinish) {
			// 待機させるフラグ
			m_condition.wait(lk, [&] {return !m_emptyFlag; });

			m_function();

			m_emptyFlag = false;
		}
	};

	// Functionを適用
	m_thread = std::thread(m_threadFunction);

	// スレッドを割り当て
	ThreadAffinity(m_thread.native_handle(), _mask);
}

Thread::~Thread() {
	// 内部のFunctionを空にする
	m_function = []() {};

	// 一応だが、空フラグをオンに
	m_emptyFlag = true;

	// スレッドを終了させる
	m_threadFinish = true;

	if (m_thread.joinable()) {
		// スレッド終了するまで待機
		m_thread.join();
	}
}

void Thread::Push(std::function<void(void)> _functuin) {
	m_function = _functuin;
	m_emptyFlag = false;
	m_condition.notify_one();
}

void Thread::Pop() {
	// からのフラグをオンにする
	m_emptyFlag = true;
	// 空のラムダ式を挿入
	m_function = [](){};
}

void Thread::Finish() {
	m_condition.notify_one();

	m_threadFinish = true;

	// スレッドが終わるまで止める
	m_thread.join();
}

}
}
