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

#define err_msg(fmt, ...)           _err_msg(__FILE_NAME__, __LINE__, fmt, ##__VA_ARGS__);
#define err_exit(fmt, ...)          _err_exit(__FILE_NAME__, __LINE__, true, fmt, ##__VA_ARGS__);
#define err_exit_now(fmt, ...)      _err_exit_now(__FILE_NAME__, __LINE__, true, fmt, ##__VA_ARGS__);
#define err_exit_en(err, fmt, ...)  _err_exit_en(__FILE_NAME__, __LINE__, true, err, fmt, ##__VA_ARGS__);
#define fatal(fmt, ...)             _fatal(__FILE_NAME__, __LINE__, true, fmt, ##__VA_ARGS__);

#else

#define err_msg(fmt, ...)           _err_msg(NULL, 0, fmt, ##__VA_ARGS__);
#define err_exit(fmt, ...)          _err_exit(NULL, 0, false, fmt, ##__VA_ARGS__);
#define err_exit_now(fmt, ...)      _err_exit_now(NULL, 0, false, fmt, ##__VA_ARGS__);
#define err_exit_en(err, fmt, ...)  _err_exit_en(NULL, 0, false, err, fmt, ##__VA_ARGS__);
#define fatal(fmt, ...)             _fatal(NULL, 0, false, fmt, ##__VA_ARGS__);

#endif


/* 
 * Prints an error message to 'stderr'
 */
void _err_msg(const char *name, size_t line, const char *fmt, ...);

/*
 * Prints an error message to 'stderr' and exits with 'EXIT_FAILURE'
 */
void _err_exit(const char *name, size_t line, bool use_abort,
                const char *fmt, ...) NORETURN;

/*
 * Prints an error message to 'stderr' and exits with 'EXIT_FAILURE'
 * It doesn't flush 'stdout'
 */
void _err_exit_now(const char *name, size_t line, bool use_abort,
                    const char *fmt, ...) NORETURN;

/* 
 * Prints the error message for 'err', 
 * an errno value, to 'stderr' and exits with 'EXIT_FAILURE'
 */
void _err_exit_en(const char *name, size_t line, bool use_abort, 
                    int err, const char *fmt, ...) NORETURN;

/*
 * Prints an error message to 'stderr' and exits 
 * with 'EXIT_FAILURE', without printing information about 'errno'
 */
void _fatal(const char *name, size_t line, bool use_abort,
            const char *fmt, ...) NORETURN;


#endif
