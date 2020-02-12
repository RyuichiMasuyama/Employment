#include "./Thread.h"
#include "./ThreadAffinity.h"

namespace mslib {
namespace thread {
Thread::Thread(unsigned int _mask) :m_emptyFlag(true) {
	// �X���b�h���I�������Ȃ�
	m_threadFinish = false;

	// �����œ���������Function�𐶐�
	m_threadFunction = [&]() {
		std::unique_lock<std::mutex> lk(m_mutex);

		while (!m_threadFinish) {
			// �ҋ@������t���O
			m_condition.wait(lk, [&] {return !m_emptyFlag; });

			m_function();

			m_emptyFlag = false;
		}
	};

	// Function��K�p
	m_thread = std::thread(m_threadFunction);

	// �X���b�h�����蓖��
	ThreadAffinity(m_thread.native_handle(), _mask);
}

Thread::~Thread() {
	// ������Function����ɂ���
	m_function = []() {};

	// �ꉞ�����A��t���O���I����
	m_emptyFlag = true;

	// �X���b�h���I��������
	m_threadFinish = true;

	if (m_thread.joinable()) {
		// �X���b�h�I������܂őҋ@
		m_thread.join();
	}
}

void Thread::Push(std::function<void(void)> _functuin) {
	m_function = _functuin;
	m_emptyFlag = false;
	m_condition.notify_one();
}

void Thread::Pop() {
	// ����̃t���O���I���ɂ���
	m_emptyFlag = true;
	// ��̃����_����}��
	m_function = [](){};
}

void Thread::Finish() {
	m_condition.notify_one();

	m_threadFinish = true;

	// �X���b�h���I���܂Ŏ~�߂�
	m_thread.join();
}

}
}
