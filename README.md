# JSON For C

JSON For C is a very simple JSON parser for the C Programming Language.

## Build

Building this project will create a shared object and headers to use this library.

```
git clone https://github.com/Ethan-Heimer/Json-For-C.git ./LibJson
cd LibJson
mkdir build && cd build
cmake ..
make
```
The most basic example to link against this library is as follows:
```
gcc -o test -I./ -L./ main.c -libjson
```

## API
The API for this library is very simple. 
### Initialization

Before Parsing, `JInit` Must be called. This initializes the JSON Abstract Syntax Tree for 
parsing and syntax Errors.

```
JInit();
```

Likewise, before the program terminates, `JEnd()` Must be called to free the AST 
and other memory the library used in the background.

```
JEnd();
```

