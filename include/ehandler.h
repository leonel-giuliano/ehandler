#ifndef __LIB_EHANDLER_H__
#define __LIB_EHANDLER_H__


#include <stddef.h>


#define EH_MSGSIZE 128


#ifdef LIBEH_DEBUG

#define err_msg(fmt, ...) _err_msg(__FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__);

#else

#define err_msg(fmt, ...) _err_msg(NULL, 0, fmt, ##__VA_ARGS__);

#endif


// Prints an error message to 'stderr'
void _err_msg(const char *name, size_t line, const char *fmt, ...);


#endif
