#include "json/jsonTreeBuilder.h"

Json* CreateJsonNode(JsonTreeType buildState, int* arrayIndex){
    Json* newNode = NewJson();
    if(newNode == NULL)
        return NULL;

    if(buildState == ARRAY){
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
        *state = ARRAY;
    else
        *state = OBJECT;

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

    AddChildNode(scopeStack, currentNode, *treeType, arrayIndex);
}

void ScopeJTreeOut(JsonStack* stack, JsonTreeType* treeType, int* arrayIndex){
    JStackPop(stack, NULL, treeType, arrayIndex);  
}

void AddChildNode(JsonStack* stack, Json** currentNode, JsonTreeType treeType, int* arrayIndex){
    Json* newNode = CreateJsonNode(treeType, arrayIndex);
    *currentNode = newNode;

    AddJsonChild(stack->head->json, newNode);
}

void FillJsonData(const Token* token, Json* currentNode, JsonTreeType treeType){
    if(treeType == OBJECT){
        if(currentNode->key == NULL){
            FillJsonField(token, &currentNode->key);
        } else { 
            FillJsonField(token, &currentNode->data);
        }
    }
    else if(treeType == ARRAY){
        FillJsonField(token, &currentNode->data);
    }
}

void FillJsonField(const Token* token, String** field){
    String* value = CreateString();
    CopyString(value, token->data);

    *field = value;
}

