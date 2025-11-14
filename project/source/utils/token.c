#include "utils/token.h"
#include "utils/string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token* CreateToken(const char* data, TokenType tokenType){
    Token* token = (Token*)malloc(sizeof(Token));

    token->data = CreateString();
    token->tokenType = tokenType;

    AppendString(token->data, data);

    return token;
}

void FreeToken(Token** token){
    if(token == NULL)
        return;

    DeleteString(&(*token)->data);
    free(*token);

    *token = NULL;
}
