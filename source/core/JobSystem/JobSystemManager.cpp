#include "./JobSystemManager.h"
#include <functional>

namespace mslib {
namespace JobSystem {

JobSystem::JobSystem() : HARDWARE_THREAD_NUM(std::thread::hardware_concurrency()) {
	for (int i = 0; i < HARDWARE_THREAD_NUM; i++) {
		//m_thread.push_back(static_cast<unsigned int>(1) << i);
	}
}

void JobSystem::SingleThreadUpdate() {
	for (auto itr : m_components) {
		itr->FixedUpdate();
	}
}

void JobSystem::MultiThread() {
	std::vector<std::function<void(void)>> m_componentUpdates;
	
	for (auto& itr : m_components) {
	/*	for (auto& itrThread : m_thread) {
			itrThread.Push([&itr]() {itr->Update(); });
		}*/
	}
}

void JobSystem::Update() {

	SingleThreadUpdate();

	MultiThread();

}

}
}