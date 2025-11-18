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

To free the resulting JSON Object when its no longer needed, call `JDelete(Json**)`

```
JDelete(&root);
```

** REMEMBER: Delete The Root JSON Object! The Root Object Is The One Returned By JParse! **

### Getting Key Value Pairs
To grab a value from a JSON object, `JGetValue(JSON object, key, value)` is called.

```
JsonValue* value = NULL;
JGetValue(root, "Hello", &JsonValue);

if(value)
    printf("Output: %s\n", value->string);
```

The result: 

```
Output: World
```

After calling `JGetValue`, If the key is found and the pair is a simple value, the value
will be stored in `JsonValue* value`. `JsonValue->string` is the text, number, or bool value 
found at the key.

If the key is not found, the value stays `NULL`.

### Getting Nested Objects

`JGetValue` will return the nested JSON object if the key is paired with one.

```
JsonValue* value = NULL;
Json* nested = JGetValue(root, "Nested-Object", value);

if(nested){
    JGetValue(nested, "Two", value);
    if(value)
        printf("Output: %s\n", value->string);
}
```

The Result:
```
Output: 2
```

### Getting Arrays

`JGetValue` Can also be used to get array values. The Key is the array index.

```
JsonValue* value = NULL;
Json* array = JGetValue(root, "Array", &value)

JGetValue(root, "0", value);
if(value)
    printf("Output 0: %s\n", value->string);

JGetValue(root, "1", value);
if(value)
    printf("Output 1: %s\n", value->string);

JGetValue(root, "2", value);
if(value)
    printf("Output 2: %s\n", value->string);
```

The result:

```
Output 0: 10
Output 1: Ten
```
