#include <string.h>

#include "ehandler.h"


static struct _opemsg _opemsg = { 0 };


void __set_opemsg(size_t line, const char *file, const char *msg) {
	_opemsg.line = line;
	strncpy(_opemsg.file, file, ABS_PATH_MAX);
	strncpy(_opemsg.msg, msg, __OPEMSGSIZ);
}


size_t __get_ehandler_line(void) {
	return (_opemsg.line) ? _opemsg.line : 0;
}


char *__get_ehandler_file(void) {
	return (_opemsg.line) ? _opemsg.file : NULL;
}
