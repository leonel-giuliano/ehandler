#include <stdio.h>
#include <unistd.h>

#include "test.h"


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

    test_msg();

    close(pfd[1]);
    return 0;
}
