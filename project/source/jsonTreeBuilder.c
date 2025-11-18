#include "json/jsonTreeBuilder.h"
#include "utils/token.h"
#include "json/json.h"

Json* CreateJsonNode(JsonTreeType buildState, int* arrayIndex){
    Json* newNode = NewJson();
    if(newNode == NULL)
        return NULL;

    if(buildState == T_ARRAY){
        String* key = CreateString();
        AppendNumber(key, *arrayIndex);
        newNode->key = key;

        *arrayIndex += 1;
    } 

    return newNode;
}

void UpdateTreeType(const Token* currentToken, JsonTreeType* state, int* arrayIndex){
    TokenType tokenType = currentToken->tokenType;
    if(tokenType == OPEN_ARRAY)
        *state = T_ARRAY;
    else
        *state = T_OBJECT;

    *arrayIndex = 0;
}

JTreeBuildState GetTreeState(const Token* currentToken){
    TokenType tokenType = currentToken->tokenType;
    if(tokenType == OPEN_OBJECT || tokenType == OPEN_ARRAY)
        return SCOPE_IN;

    if(tokenType == CLOSE_OBJECT || tokenType == CLOSE_ARRAY)
        return SCOPE_OUT;

    if(tokenType == NEW_DATA)
        return INLINE_NEW;

    if(tokenType == DATA)
        return DATA_FILL;

    return UNDEFINED;
}

void ScopeJTreeIn(Token* token, Json** currentNode, JsonStack* scopeStack, JsonTreeType* treeType, int* arrayIndex){
    JStackPush(scopeStack, *currentNode, *treeType, *arrayIndex);    
    UpdateTreeType(token, treeType, arrayIndex);

    JsonType type;
    if(token->tokenType == OPEN_ARRAY){
        type = ARRAY;
    }
    else if(token->tokenType == OPEN_OBJECT){
        type = OBJECT;
    }
    (*currentNode)->type = type;

    AddChildNode(VALUE, scopeStack, currentNode, *treeType, arrayIndex);

    if((*currentNode)->type == ARRAY)
        printf("ARRAY Made\n");
    else if((*currentNode)->type == OBJECT)
        printf("OBJECT Made\n");
}

void ScopeJTreeOut(JsonStack* stack, JsonTreeType* treeType, int* arrayIndex){
    JStackPop(stack, NULL, treeType, arrayIndex);  
}

void AddChildNode(JsonType type, JsonStack* stack, Json** currentNode, JsonTreeType treeType, int* arrayIndex){
    Json* newNode = CreateJsonNode(treeType, arrayIndex);
    *currentNode = newNode;

    newNode->type = type;

    AddJsonChild(stack->head->json, newNode);
}

void FillJsonData(const Token* token, Json* currentNode, JsonTreeType treeType){
    if(treeType == T_OBJECT){
        if(currentNode->key == NULL){
            FillJsonField(token, &currentNode->key);
        } else { 
            FillJsonField(token, &currentNode->data);
        }
    }
    else if(treeType == T_ARRAY){
        FillJsonField(token, &currentNode->data);
    }
}

void FillJsonField(const Token* token, String** field){
    String* value = CreateString();
    CopyString(value, token->data);

    *field = value;
}

