#include "json/json.h"
#include "json/jsonStack.h"

#include <stdlib.h>

JsonStack* NewJsonStack(){
    JsonStack* stack = (JsonStack*)malloc(sizeof(JsonStack));
    if(stack == NULL){
        printf("Falied to create Stack");
        return NULL;
    }

    stack->head = NULL;

    return stack;
}

JsonStackNode* NewJsonStackNode(Json* data, JsonTreeType state, int arrayIndex){
    JsonStackNode* node = (JsonStackNode*)malloc(sizeof(JsonStackNode));
    if(node == NULL){
        printf("Failed to create Node");
        return NULL;
    }

    node->json = data;
    node->state = state;
    node->arrayIndex = arrayIndex;

    node->next = NULL;
    
    return node;
}

void DeleteJsonStack(JsonStack** stack){
    if(*stack == NULL)
        return;

    while((*stack)->head != NULL){
        JStackPop(*stack, NULL, NULL, NULL);
    }

    free(*stack);
    *stack = NULL;
}

void DeleteJsonStackNode(JsonStackNode** node){
    if(*node == NULL)
        return;

    free(*node);
    *node = NULL;
}

void JStackPush(JsonStack* stack, Json* data, JsonTreeType state, int index){
    if(stack == NULL || data == NULL)
        return;

    JsonStackNode* node = NewJsonStackNode(data, state, index);
    if(node == NULL)
        return;
    
    node->next = stack->head;
    stack->head = node;
}

void JStackPop(JsonStack* stack, struct Json** json, JsonTreeType* state, int* index){
    if(stack->head == NULL)
        return;

    JsonStackNode* node = stack->head;
    stack->head = stack->head->next;

    if(json != NULL)
        *json = node->json;

    if(state != NULL)
        *state = node->state;

    if(index != NULL)
        *index = node->arrayIndex;

    DeleteJsonStackNode(&node); 
}
