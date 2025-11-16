# EHandler
C library for handling errors

## Usage
For standard usage of `EHANDLER()` and `EHANDLER_GOTO()`, it would be recommended to only use the header file, given that the library file is only for `set_opemsg`
Including it doesn't give an error, it just defines a global variable that wouldn't be used in the program

- The functions `EHANDLER(_Msg, _ExitVal)` and `EHANDLER_GOTO(_Msg, _ExitVal, _GotoLabel)` should be called when an error happens, printing information about it
- `EHANDLER_GOTO(_Msg, _ExitVal, _GotoLabel)` expects a variable called `e` to be defined in the function where it was called in order to save the `_ExitVal` (the name of the variable can be changed in the header file)
- In order to use `set_opemsg(const char *msg)`, `USE_OPEMSG` needs to be declared before includeing the header file, or it won't do anything. This could also be done setting the macro while compiling

Checkout [examples](examples/) to see example codes on how to implement it


## Installation
You could just download the [ehandler.h](include/ehandler.h) if you are not planning on using the `set_opemsg()` function
Or you could use:
```bash
git clone https://github.com/leonel-giuliano/ehandler.git
mkdir build && cd build
cmake ..
make

# If you want to install it locally
sudo make install

```
