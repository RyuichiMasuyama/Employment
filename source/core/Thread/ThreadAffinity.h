#pragma once

#ifdef WINDOWS
#include <Windows.h>
#endif

namespace mslib {
namespace thread {
void ThreadAffinity(void *_handle, DWORD _mask) {
#ifdef WINDOWS
	SetThreadAffinityMask(_handle, _mask);
#endif
}
}
}