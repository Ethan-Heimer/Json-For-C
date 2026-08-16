# JSON For C

JSON For C is a very __simple__ JSON parser for the C Programming Language. Parse 
the string, get what you need, and get out.

__This Library is NOT for writting or serializing JSON files.__
Just reading!

## Build

Building this project will create a shared object and headers to use this library.

```
git clone https://github.com/Ethan-Heimer/Json-For-C.git ./LibJson
cd LibJson
mkdir build && cd build
cmake ..
make
```

or using cmake:
```
add_subdirectory("${CMAKE_SOURCE_DIR}/PATH_TO_JSON_FOR_C_DIR")
...
target_link_libraries(${NAME} PRIVATE jsonlib)
```

The most basic example to link against this library is as follows, where the
project is being built within the build directory generated.

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
        "One": 1,
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
After initialization, parsing can begin. To parse a file, call `JParseFile(file name)`

```example.c
Json* root = JParseFile("example.json");
```

Or a string, call `JParseString(const char* string)`
```example.c
Json* root = JParseString("...");
```

`JParse*` will return a JSON object to be interpreted. This JSON object represents the 
root of the file.

If the object returned is NULL, then an error occured while parsing. The Error
is printed by the library.

To free the resulting JSON Object when its no longer needed, call `JDelete(Json**)`

```example.c
JDelete(&root);
```

__REMEMBER: Delete The Root JSON Object, Or you will leak memory!__

### Getting Key Value Pairs
To grab a value from a JSON object, `JGetValue(JSON object, key, value)` is called.

```example.c
JsonValue hello;
JGetValue(root, "Hello", &hello);

if(hello.hasValue)
    printf("Output: %s\n", hello.value->string);
```

The result: 

```
Output: World
```

After calling `JGetValue`, If the key is found and the pair is a simple value, the value
will be stored in `JsonValue hello`. `hello.value->string` is the text, number, or bool value 
found at the key.

If the key is not found, `hello.hasValue` is false.

`JsonValue` objects have flags that can be used to determine its value's type
(ie. `.isString`, `.isInt`, `.isFloat`, `.isNull`, `.isBool`).

### Getting Nested Objects

`JGetValue` will return the nested JSON object if the key is paired with one.

```example.c
JsonValue value;
Json* nested = JGetValue(root, "Nested-Object", &value);

if(nested){
    JGetValue(nested, "Two", value);
    if(value.hasValue)
        printf("Output: %s\n", value.value->string);
}
```

The Result:
```
Output: 2
```

### Getting Arrays

`JGetValue` Can also be used to get array values. The Key is the array index.

```example.c
JsonValue element;
Json* array = JGetValue(root, "Array", &element)

JGetValue(array, "0", &element);

if(element.hasValue)
    printf("Output 0: %s\n", element.value->string);

JGetValue(root, "1", &element);
if(element.hasValue)
    printf("Output 1: %s\n", element.value->string);

JGetValue(root, "2", &element);
if(element.hasValue)
    printf("Output 2: %s\n", element.value->string);
```

The result:

```
Output 0: 10
Output 1: Ten
```

__The element at index 2 is an object, so its not stored in value, but returned by JGetValue()__

Looping through an array is simple. JSON Objects store the type of object it is (VALUE, OBJECT, ARRAY),
and its number if children. Using that information, looping throught all elements can be achieved like so:

```example.c
int children = array->childCount;
for(int i = 0; i < children; i++){
    char buffer[20];
    sprintf(buffer, "%s", i);

    JGetValue(array, buffer, &element);
    if(element.hasValue)
        printf("Value at %d is %s\n", i, element.value->string);
}
```

The Result: 

```
Value at 0 is 10
Value at 1 is Ten
```
