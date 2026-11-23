#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "ename.h"


#define MSG_SIZE 64

// Returns the size of the message starting from the seek
#define SK_MSGSIZ(sk, msg) (sizeof(msg) - ((sk) - (msg)))

// Updates 'sk' so if it was out of bounds, it points to the '\0'
#define SK_MSGBOUND(sk, msg) do {                                   \
    if((sk) - (msg) >= sizeof(msg)) (sk) = (msg) + sizeof(msg) - 1; \
} while(0);


/*
 * Prints the error message including the file and line 
 * (if 'name' isn't NULL), the errno (if 'err' isn't 0) and the message
 *
 * The message is truncated if 'MSG_SIZE' is overflowed
 */
static void print_msg(const char *name, int line, int err, 
                    const char *fmt, va_list ap) {
    char  msg[MSG_SIZE];
    char *sk_msg;

    sk_msg = msg;
    if(name != NULL) {
        sk_msg += snprintf(msg, sizeof(msg), "(%s:%d): ", name, line);
        SK_MSGBOUND(sk_msg, msg);
    }

    sk_msg += strlcpy(sk_msg, "ERROR", SK_MSGSIZ(sk_msg, msg));
    SK_MSGBOUND(sk_msg, msg);

    if(err) {
        sk_msg += snprintf(sk_msg, SK_MSGSIZ(sk_msg, msg), 
                            " [%s:%d]", ename[err], err);
        SK_MSGBOUND(sk_msg, msg);
    }

    sk_msg += strlcpy(sk_msg, ": ", SK_MSGSIZ(sk_msg, msg));
    SK_MSGBOUND(sk_msg, msg);

    vsnprintf(sk_msg, SK_MSGSIZ(sk_msg, msg), fmt, ap);
    fprintf(stderr, "%s", msg);
}
