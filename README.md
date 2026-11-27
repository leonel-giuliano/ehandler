# ehandler

Small C library for error handling.


## Install

```bash
git clone https://github.com/leonel-giuliano/ehandler.git
cd ehandler
make
# Then copy the generated files and 'include/ehandler.h' to your project


# If you would like to install the library to your local libs
make install
```

And to uninstall:
```bash
make clean
make uninstall
```


## Usage

Include the header to the project like:
```c
#include "ehandler.h"
```

And add the `-leh` when compiling.  
This makes the errors get printed like:
```c
err_msg("there was a problem")  // ERROR [ENOENT:2]: there was a problem
```

If info about the file and line where the error happened (when the function gets called)
is needed, then `LIBEH_DEBUG` needs to be declared before including the header file
```c
#define LIBEH_DEBUG
#include "ehandler.h"

err_msg("there was a problem") // (main:3): ERROR [ENOET:2]: there was a problem
```


## API Reference

```c
void err_msg(const char *restrict fmt, ...);
```

Prints an error message to `stderr` with info about `errno`, flushing `stdout` first

```c
void err_exit(const char *restrict fmt, ...);
```

Prints an error message to `stderr` with info about `errno`, flushing `stdout` first.  
Exits the program with `abort` if `LIBEH_DEBUG` is defined, or with `exit(EXIT_FAILURE)`

```c
void err_exit_now(const char *restrict fmt, ...);
```

Prints an error message to `stderr` with info about `errno`, without flushing `stdout`.  
Exits the program with `abort` if `LIBEH_DEBUG` is defined, or with `_exit(EXIT_FAILURE)`

```c
void err_exit_en(int errno_val, const char *restrict fmt, ...);
```

Prints an error message to `stderr` with info about `errno_val`, flushing `stdout` first.  
Exits the program with `abort` if `LIBEH_DEBUG` is defined, or with `exit(EXIT_FAILURE)`

```c
void fatal(const char *restrict fmt, ...);
```

Prints an error message to `stderr` without any info about `errno`, flushing `stdout` first.  
Exits the program with `abort` if `LIBEH_DEBUG` is defined, or with `exit(EXIT_FAILURE)`.


## Credits

This project is an independent implementation based on the concepts and examples presented in:

- **Book:** *The Linux Programming Interface*
- **Author:** Michael Kerrisk
- **Chapter:** 3 – System Programming Concepts
- **Section:** 3.5 – Notes on the Example Programs in This Book

The implementation was written independently for educational purposes. All credit for the original concepts and material belongs to the respective author.
