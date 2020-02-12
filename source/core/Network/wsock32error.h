#ifndef __GN31_WINSOCK32_ERROR_POPUP__
#define __GN31_WINSOCK32_ERROR_POPUP__

#include <windows.h>
#pragma comment (lib, "wsock32.lib")

struct errdata_t{
	int	eno;					// エラーコード
	const char* errmsg;				// エラーメッセージ
};

void errcom(int errcode);
void ErrorLog();
#endif
