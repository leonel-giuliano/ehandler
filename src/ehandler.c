#include "ehandler.h"


#ifdef USE_OPEMSG


#include <string.h>


struct _opemsg _opemsg = { 0 };


void __set_opemsg(size_t line, const char *file, const char *msg) {
	_opemsg.line = line;
	strncpy(_opemsg.file, file, ABS_PATH_MAX);
	strncpy(_opemsg.msg, msg, __OPEMSGSIZ);
}


#endif
