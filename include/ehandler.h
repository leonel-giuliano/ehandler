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


#define EHANDLER(_Msg, _ExitVal) do {	\
	emsg(__LINE__, __FILE__, _Msg);		\
	exit(_ExitVal);						\
} while(0)


#define EHANDLER_GOTO(_Msg, _ExitVal, _GotoLabel) do {	\
	emsg(__LINE__, __FILE__, _Msg);						\
	e = (_ExitVal);										\
	goto _GotoLabel;									\
} while(0)


size_t __get_ehandler_line(void) 	__attribute__((weak));
char *__get_ehandler_file(void) 	__attribute__((weak));
void __print_emsg(void)				__attribute__((weak));


static inline size_t get_ehandler_line(void) {
	return (__get_ehandler_line != NULL) ? __get_ehandler_line() : 0;
}


static inline char *get_ehandler_file(void) {
	return (__get_ehandler_file != NULL) ? __get_ehandler_file() : NULL;
}


static inline void print_emsg(void) {
	if(__print_emsg != NULL) __print_emsg();
}


static inline void emsg(size_t line, const char *file, const char *msg) {
	int 	errno_val = errno;
	size_t 	ehline 	= get_ehandler_line();
	char 	*ehfile = get_ehandler_file();

	if(!ehline) {
		ehline = line;
		ehfile = (char *)file;
	}

	fprintf(stderr, "\n(%s:%zu) ERROR: %s", ehfile, ehline, msg);
	print_emsg();

	if(errno_val > 0)
		fprintf(stderr, " | %s [ERRNO::%d]", strerror(errno_val), errno_val);

	putc('\n', stderr);
}


#endif // !__LIBEHANDLER_H__
