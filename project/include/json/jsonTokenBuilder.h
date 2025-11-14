#ifndef JSON_TOKEN_BUILDER_H
#define JSON_TOKEN_BUILDER_H

#include "utils/queue.h"
#include "utils/ast.h"
#include "utils/token.h"

typedef enum TokenizeType{
    PUSH,
    HOLD
} TokenizeType;

void AddNumericCharactersToNode(ASTNode* parentNode, ASTNode** childNodes, int childCount);
void AddAsciiToNode(ASTNode* parentNode, ASTNode** childNodes, int childCount);
void AddBooleanValues(ASTNode* parentNode, ASTNode** childNodes, int childCount);

void Tokenize(ASTNode* currentSyntaxNode, char currentChar, String* tokenString, Queue* queue, TokenizeType* tokenState);
void PushToken(Queue* queue, String* dataString, TokenType type);

void UpdateScope(ASTNode* currentSyntaxNode, unsigned int* scope);

bool ValidateToken(ASTNode** currentASTNode, char token);
bool DiscardToken(ASTNode* currentSyntaxNode);
bool ChangeTokenizingState(ASTNode* currentSyntaxNode, TokenizeType* currentState);

#endif
