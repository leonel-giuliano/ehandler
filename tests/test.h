#ifndef __LIBEH_TEST_H__
#define __LIBEH_TEST_H__


#include <stddef.h>


#define BUF_SIZE 128

#define CHECK(res, line) check(__FILE_NAME__, __LINE__, res, line)


void check(const char *name, size_t line, const char *res, size_t res_line);

void test_msg(void);
void test_exit(void);


extern int pfd[2];


#endif
