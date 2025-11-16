#ifndef __LIBEHANDLER_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#ifdef __linux__
#include <linux/limits.h>
#define ABS_PATH_MAX PATH_MAX
#elif __unix__
#include <limits.h>
#define ABS_PATH_MAX ABS_PATH_MAX
#elif _WIN32
#include <windows.h>
#define ABS_PATH_MAX MAX_PATH
#endif


#define __OPEMSGSIZ 64


struct _opemsg {
	size_t 	line;
	char 	file[ABS_PATH_MAX];
	char 	msg[__OPEMSGSIZ];
};


#define EMSG(_Msg) do {																\
	int __errno_val = errno;														\
	fprintf(stderr, "\n(%s:%d) ERROR: %s", __FILE__, __LINE__, _Msg);				\
	if(__errno_val > 0)																\
		fprintf(stderr, " | %s [ERRNO::%d]", strerror(__errno_val), __errno_val);	\
	putc('\n', stderr);																\
} while(0)


#define EHANDLER(_Msg, _ExitVal) do {	\
	EMSG(_Msg);							\
	exit(_ExitVal);						\
}


#define EHANDLER_GOTO(_Msg, _ExitVal, _GotoLabel) do {	\
	EMSG(_Msg);											\
	e = (_ExitVal);										\
	goto _GotoLabel;									\
} while(0);


#endif // !__LIBEHANDLER_H__
