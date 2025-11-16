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


#ifdef USE_OPEMSG

#define __EHANDLER_LINE (_opemsg.line) 				? _opemsg.line : __LINE__
#define __EHANDLER_FILE (_opemsg.file[0] != '\0') 	? _opemsg.file : __FILE__
#define set_opemsg(msg) __set_opemsg(__LINE__, __FILE__, msg)

#define PRINT_OPEMSG() do {									\
	if(_opemsg.line) fprintf(stderr, " - %s", _opemsg.msg);	\
} while(0)

extern struct _opemsg _opemsg;

void __set_opemsg(size_t line, const char *file, const char *msg);

#else

#define __EHANDLER_LINE __LINE__
#define __EHANDLER_FILE __FILE__
#define set_opemsg(msg) 
#define PRINT_OPEMSG()

#endif


#define EMSG(_Msg) do {																\
	int __errno_val = errno;														\
	fprintf(stderr, "\n(%s:%d) ERROR: %s", __EHANDLER_FILE, __EHANDLER_LINE, _Msg);	\
	PRINT_OPEMSG();																	\
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
