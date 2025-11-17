#ifndef JSON_STACK_H
#define JSON_STACK_H

#include "json/json.h"
#include "json/jsonTree.h"

struct JsonStack;
struct JsonStackNode;

typedef struct JsonStack{
    struct JsonStackNode* head;
} JsonStack;

typedef struct JsonStackNode{
    struct Json* json;
    JsonTreeType state;
    int arrayIndex;

    struct JsonStackNode* next;
} JsonStackNode;

JsonStack* NewJsonStack();
JsonStackNode* NewJsonStackNode(struct Json* data,  JsonTreeType state, int index);

void DeleteJsonStack(JsonStack** stack);
void DeleteJsonStackNode(JsonStackNode** node);

void JStackPush(JsonStack* stack, struct Json* data, JsonTreeType state, int index);
void JStackPop(JsonStack* stack, struct Json** jsonn, JsonTreeType* state, int* index);

#endif
