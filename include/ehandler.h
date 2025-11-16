#ifndef __LIBEHANDLER_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


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
