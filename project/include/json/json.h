#ifndef JSON_H
#define JSON_H

#include "utils/token.h"
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "utils/queue.h"
#include "utils/ast.h"

extern ASTTree* syntaxTree;

typedef struct JsonValue{
    String* value;
    bool isInt;
    bool isFloat;
    bool isBool;
    bool isNull;
    bool isString;
    bool hasValue;
} JsonValue;

typedef enum JsonType{
    VALUE = 0,
    OBJECT,
    ARRAY
} JsonType;

typedef struct Json{
    String* key;
    String* data;

    struct Json** children;
    int childLength;

    JsonType type;
    TokenValueType valueType;
} Json;

//this initializes the syntax token map, and abstract syntax trees
void JInit();

//jparse should return a JSON tree at some point
Json* JParseFile(const char* filePath);
Json* JParseString(const char* string);

Json* JGetValue(Json* root, const char* key, JsonValue* value);

//this will tokenize the json file, checks syntax as a side effect
bool JFileTokenize(String* normalizedFile, Queue* tokenQueue);

//create JSON Tree
Json* JCreateTree(Queue* tokenQueue);

//delete Json tree
void JDelete(Json**);

//delete syntax tree and other gloabl memory
void JEnd();

#ifdef __cplusplus
}
#endif

#endif
