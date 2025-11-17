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


