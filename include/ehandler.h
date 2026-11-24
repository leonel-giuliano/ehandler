#ifndef __LIB_EHANDLER_H__
#define __LIB_EHANDLER_H__


#include <stddef.h>
#include <stdbool.h>


#define EH_MSGSIZE 128


#ifdef __GNUC__
#define NORETURN __attribute((noreturn))
#else
#define NORETURN
#endif


#ifdef LIBEH_DEBUG

#define err_msg(fmt, ...)   _err_msg(__FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__);
#define err_exit(fmt, ...)  _err_exit(__FILE_NAME__, __LINE__, true, fmt, ##__VA_ARGS__);

#else

#define err_msg(fmt, ...)   _err_msg(NULL, 0, fmt, ##__VA_ARGS__);
#define err_exit(fmt, ...)  _err_exit(NULL, 0, false, fmt, ##__VA_ARGS__);

#endif


// Prints an error message to 'stderr'
void _err_msg(const char *name, size_t line, const char *fmt, ...);

// Prints an error message to 'stderr' and exits with 'EXIT_FAILURE'
void _err_exit(const char *name, size_t line, bool use_abort,
                const char *fmt, ...) NORETURN;


#endif
