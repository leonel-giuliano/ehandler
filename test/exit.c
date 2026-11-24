#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

#include "ehandler.h"
#include "test.h"


#define ISOLATE_ERR(msg) isolate_err(__FILE_NAME__, __LINE__, msg)


static void isolate_err(const char *name, size_t line, const char *msg) {
    pid_t pid;

    switch (pid = fork()) {
    case 0: _err_exit(name, line, false, msg);
    case -1:
        printf("(%s:%zu) - fork", name, line);
        exit(EXIT_FAILURE);
    }

    waitpid(pid, NULL, 0);
}


void test_exit(void) {
    char buf[BUF_SIZE];

    ISOLATE_ERR("This is the first example");
    CHECK("ERROR: This is the first example", __LINE__ - 1);

    snprintf(buf, sizeof(buf), "This is the %d° example", 2);
    ISOLATE_ERR(buf);
    CHECK("ERROR: This is the 2° example", __LINE__ - 1);

    errno = 2;
    snprintf(buf, sizeof(buf), "This is the %d° example", 3);
    ISOLATE_ERR(buf);
    CHECK("ERROR [ENOENT:2]: This is the 3° example", __LINE__ - 1);
    errno = 0;
}
