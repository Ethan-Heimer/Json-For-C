#ifndef JSON_H
#define JSON_H

#include <stdio.h>
#include "utils/queue.h"
#include "utils/ast.h"
#include "utils/token.h"

extern ASTTree* syntaxTree;

typedef String JsonValue;

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
} Json;

//this initializes the syntax token map, and abstract syntax trees
void JInit();

//jparse should return a JSON tree at some point
Json* JParse(const char* filePath);

Json* JGetValue(Json* root, const char* key, JsonValue** value);

//this will tokenize the json file, checks syntax as a side effect
bool JFileTokenize(String* normalizedFile, Queue* tokenQueue);

//create JSON Tree
Json* JCreateTree(Queue* tokenQueue);

//delete Json tree
void JDelete(Json**);

//delete syntax tree and other gloabl memory
void JEnd();

#endif
