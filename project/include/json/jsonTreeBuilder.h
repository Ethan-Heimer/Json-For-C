#ifndef JSON_TREE_BUILD_H
#define JSON_TREE_BUILD_H

#include "json/json.h"
#include "json/jsonTree.h"
#include "json/jsonStack.h"

typedef enum JTreeBuildState{
    UNDEFINED,
    SCOPE_IN,
    SCOPE_OUT,
    INLINE_NEW,
    DATA_FILL
} JTreeBuildState;

JTreeBuildState GetTreeState(const Token* currentToken);
Json* CreateJsonNode(JsonTreeType buildState, int* arrayIndex);

void UpdateTreeType(const Token* currentToken, JsonTreeType* state, int* arrayIndex);

void ScopeJTreeIn(Token* token, Json** currentNode, JsonStack* scopeStack, JsonTreeType* treeType, int* arrayIndex);
void ScopeJTreeOut(JsonStack* stack, JsonTreeType* treeType, int* arrayIndex);

void AddChildNode(JsonType type, JsonStack* stack, Json** currentNode, JsonTreeType treeType, int* arrayIndex);

void FillJsonField(const Token* token, String** field);
void FillJsonData(const Token* token, Json* currentNode, JsonTreeType treeType);

#endif
