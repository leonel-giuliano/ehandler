#include <errno.h>

#include "ehandler.h"
#include "test.h"


void test_msg(void) {
    err_msg("This is the first example");
    CHECK("ERROR: This is the first example", __LINE__ - 1);

    err_msg("This is the %d° example", 2);
    CHECK("ERROR: This is the 2° example", __LINE__ - 1);

    errno = 2;
    err_msg("This is the %d° example", 3);
    CHECK("ERROR [ENOENT:2]: This is the 3° example", __LINE__ - 1);
    errno = 0;
}
