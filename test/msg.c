#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "ehandler.h"


#define BUF_SIZE 128

#define CHECK(res, line) check(__FILE_NAME__, __LINE__, res, line)


int pfd[2];


static void check(const char *name, size_t line, 
                    const char *res, size_t res_line) {
    char    buf[BUF_SIZE], res_buf[BUF_SIZE];
    ssize_t len;

    snprintf(res_buf, sizeof(res_buf), "\n(%s:%zu): %s\n", name, res_line, res);

    if((len = read(pfd[0], buf, sizeof(buf) - 1)) == -1) {
        printf("(%s:%zu): READ ERROR", name, line);
        exit(EXIT_FAILURE);
    }

    buf[len] = '\0';
    if(strcmp(buf, res_buf)) {
        printf("(%s:%zu): Assertion error '%s' != '%s'", 
                name, line, buf, res_buf);

        exit(EXIT_FAILURE);
    }
}


int main(void) {

    // Allows checking the output
    if(pipe(pfd) == -1) {
        perror("pipe");
        return 1;
    }

    if(dup2(pfd[1], STDERR_FILENO) == -1) {
        perror("dup2");
        return 1;
    }

    close(pfd[1]);

    err_msg("This is the first example");
    CHECK("ERROR: This is the first example", __LINE__ - 1);

    err_msg("This is the %d° example", 2);
    CHECK("ERROR: This is the 2° example", __LINE__ - 1);

    errno = 2;
    err_msg("This is the %d° example", 3);
    CHECK("ERROR [ENOENT:2]: This is the 3° example", __LINE__ - 1);
    errno = 0;

    close(pfd[0]);
    return 0;
}
