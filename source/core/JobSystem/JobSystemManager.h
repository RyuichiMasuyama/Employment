#pragma once

#include <Singleton.h>

#include "./core/Object/object.h"
#include "./core/Thread/Thread.h"

namespace mslib {
namespace JobSystem {
class JobSystem :public pattern::Singleton<JobSystem> {
private:
	JobSystem();
	~JobSystem() = default;


	void SingleThreadUpdate();
	void MultiThread();
	
public:
	const unsigned int HARDWARE_THREAD_NUM;

	void Update();
	
	std::list< component::ComponentSPtr > m_components;

	//std::vector< mslib::thread::Thread > m_thread;
};
}
}