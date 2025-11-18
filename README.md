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

```example.c
Json* root = JParse("example.json");
```

`JParse` will return a JSON object to be interpreted. This JSON object represents the 
root of the file.

If the object returned is NULL, then an error occured while parsing.

To free the resulting JSON Object when its no longer needed, call `JDelete(Json**)`

```example.c
JDelete(&root);
```

__REMEMBER: Delete The Root JSON Object! The Root Object Is The One Returned By JParse()!__

### Getting Key Value Pairs
To grab a value from a JSON object, `JGetValue(JSON object, key, value)` is called.

```example.c
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

```example.c
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

```example.c
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

__The element at index 2 is an object, so its not stored in value, but returned by JGetValue()__

Looping through an array is simple. JSON Objects store the type of object it is (VALUE, OBJECT, ARRAY),
and its number if children. Using that information, looping throught all elements can be achieved like so:

```example.c
int children = array->childCount;
for(int i = 0; i < children; i++){
    char buffer[20];
    sprintf(buffer, "%s", i);

    JGetValue(array, buffer, &value);
    if(value)
        printf("Value at %d is %s\n", i, value->string);
}
```

The Result: 

```
Value at 0 is 10
Value at 1 is Ten
```
