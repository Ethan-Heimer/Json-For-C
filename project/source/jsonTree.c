#include "json/jsonTree.h"
#include "utils/string.h"

#include <stdlib.h>
#include <stdio.h>

Json* NewJson(){
    Json* json = (Json*)malloc(sizeof(Json));

    json->key = NULL;
    json->data = NULL;

    json->children = NULL;
    json->childLength = 0;

    return json;
}

void DeleteJson(Json** node){
    if(*node == NULL)
        return;

    if((*node)->key != NULL)
        DeleteString(&(*node)->key);

    if((*node)->data != NULL)
        DeleteString(&(*node)->data);

    for(int i = 0; i < (*node)->childLength; i++)
        DeleteJson(&(*node)->children[i]);

    *node = NULL;
}

void AddJsonChild(Json* parent, Json* child){
    int newSize = parent->childLength + 1;
    Json** buffer = (Json**)realloc(parent->children, newSize * sizeof(Json*));

    if(buffer == NULL){
        printf("Cannot add child to json");
    }

    buffer[newSize-1] = child;

    parent->children = buffer;
    parent->childLength = newSize;
}
