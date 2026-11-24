#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"


int pfd[2];


void check(const char *name, size_t line, 
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
