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

Likewise, before the program terminates, `JEnd` Must be called to free the AST 
and other memory the library used in the background.

```
JEnd();
```

### Parsing

To show off the API, the following, `example.json` will be used: 
```example.json
{
    "Hello" : "World",

    "Nested-Object" : {
        "One", 1,
        "Two" : 2, 
        "Three" : 3
    },

    "Array" : [
        10,
        "Ten",
        {
            "Ten" : 10
        }
    ]
}   
```
After initialization, parsing can begin. To parse a file, call `JParse(file name)`

```
Json* root = JParse("example.json");
```

`JParse` will return a JSON object to be interpreted. This JSON object represents the 
root of the file.

If the object returned is NULL, then an error occured while parsing.

### Getting Key Value Pairs
To grab a value from a JSON object, `JGetValue(JSON object, key, value)` is called.

```
JsonValue* value = NULL;
JGetValue(json, "Hello", &JsonValue);

if(value)
    printf("Value: %s\n", value->string);
```

After calling `JGetValue`, If the key is found and the pair is a simple value, the value
will be stored in `JsonValue* value`. `JsonValue->string` is the text, number, or bool value 
found at the key.

If the key is not found, the value stays `NULL`.


