#ifndef JSON_H
#define JSON_H

#include <stdio.h>
#include "utils/queue.h"
#include "utils/ast.h"
#include "utils/token.h"

#include "jsonTree.h"
#include "jsonStack.h"

extern ASTTree* syntaxTree;

typedef String JsonValue;

//this initializes the syntax token map, and abstract syntax trees
void JInit();

//jparse should return a JSON tree at some point
Json* JParse(const char* filePath);

Json* JGetValue(Json* root, const char* key, JsonValue** value);

//this will tokenize the json file, checks syntax as a side effect
bool JFileTokenize(String* normalizedFile, Queue* tokenQueue);

//create JSON Tree
Json* JCreateTree(Queue* tokenQueue);

//delete syntax tree and other gloabl memory
void JEnd();

#endif
