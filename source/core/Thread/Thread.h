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
	// ����
	std::condition_variable m_condition;
	std::thread m_thread;
	std::mutex m_mutex;
	
	// �؂�ւ��\��Funcion
	std::function<void(void)> m_function;

	// Thread�����œ���������Function
	std::function<void(void)> m_threadFunction;

	// �؂�ւ��\Function����
	bool m_emptyFlag;

	// �X���b�h���I��������t���O
	bool m_threadFinish;
};
}
}