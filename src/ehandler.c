#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "ehandler.h"
#include "ename.h"


static void terminate(bool use_abort, bool exit_now) NORETURN;


/*
 * Appends the message, making sure that 'sk' doesn't go beyond 'end'
 * 'p_sk' is updated to point to the end of the message
 */
static void vappend_msg(char **p_sk, char *end, const char *fmt, va_list ap) {
    size_t  size, n_wrt;

    if(*p_sk >= end) return;

    size    = end - *p_sk;
    n_wrt   = vsnprintf(*p_sk, size, fmt, ap);

    if(n_wrt < size)    *p_sk += n_wrt;
    else                *p_sk  = end;
}


/*
 * Appends the message, making sure that 'sk' doesn't go beyond nor up to 'end'
 * 'p_sk' is updated to point to the end of the message
 */
static void append_msg(char **p_sk, char *end, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    vappend_msg(p_sk, end, fmt, ap);
    va_end(ap);
}


/*
 * Prints the error message including the file and line 
 * (if 'name' isn't NULL), the errno (if 'err' isn't 0) and the message
 *
 * The message is truncated if 'MSG_SIZE' is overflowed
 */
static void print_msg(const char *name, size_t line, int err, bool flush,
                    const char *fmt, va_list ap) {
    char  msg[EH_MSGSIZE];
    char *sk, *end;

    sk  = msg;
    end = msg + sizeof(msg);

    if(name != NULL) append_msg(&sk, end, "(%s:%zu): ", name, line);

    append_msg(&sk, end, "ERROR");
    if(err) append_msg(&sk, end, " [%s:%d]", ename[err], err);

    append_msg(&sk, end, ": ");
    vappend_msg(&sk, end, fmt, ap);

    if(flush) fflush(stdout);
    fprintf(stderr, "\n%s\n", msg);
    fflush(stderr);
}


/*
 * Terimates the program either with 'abort', 
 * or with '_exit' if 'exit_now' is true or 'exit'
 */
static void terminate(bool use_abort, bool exit_now) {
    if(use_abort) abort();

    if(exit_now) _exit(EXIT_FAILURE);
    exit(EXIT_FAILURE);
}


void _err_msg(const char *name, size_t line, const char *fmt, ...) {
    int     err;
    va_list ap;

    err = errno;

    va_start(ap, fmt);
    print_msg(name, line, err, true, fmt, ap);
    va_end(ap);
}


void _err_exit(const char *name, size_t line, bool use_abort, 
                const char *fmt, ...) {
    int     err;
    va_list ap;

    err = errno;

    va_start(ap, fmt);
    print_msg(name, line, err, true, fmt, ap);
    va_end(ap);

    terminate(use_abort, false);
}


void _err_exit_now(const char *name, size_t line, bool use_abort, 
                    const char *fmt, ...) {
    int     err;
    va_list ap;

    err = errno;

    va_start(ap, fmt);
    print_msg(name, line, err, false, fmt, ap);
    va_end(ap);

    terminate(use_abort, true);
}


void _err_exit_en(const char *name, size_t line, bool use_abort, 
                    int err, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    print_msg(name, line, err, true, fmt, ap);
    va_end(ap);

    terminate(use_abort, false);
}


void _fatal(const char *name, size_t line, bool use_abort, 
            const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    print_msg(name, line, 0, true, fmt, ap);
    va_end(ap);

    terminate(use_abort, false);
}
