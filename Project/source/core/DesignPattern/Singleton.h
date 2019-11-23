#pragma once

#include <memory>

namespace mslib {
namespace pattern {

// Singleton
 template <class T>
class Singleton {
	using UniquePtr = std::unique_ptr<T>;

public:
	inline static T& GetInstance() {
		static typename T::UniquePtr singleton(T::Create());
		return Get(singleton);
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

protected:
	Singleton() = default;
	~Singleton() = default;

private:
	inline static T* Create() { return new T(); }
	inline static T& Get(const UniquePtr &ptr) { return *ptr; }
};

}
}
