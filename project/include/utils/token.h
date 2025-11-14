#ifndef TOKEN_H
#define TOKEN_H

#define MAX_TOKEN_LENGTH 255

#include "utils/string.h"

typedef enum TokenType{
    //abstract token types
    INVALID = 0,
    VALID,

    //specific token types
    //data tokens
    DATA = 2,
    TEXT_DATA = 3,
    NUMBER_DATA = 4,
    KEY,

    //scope tokens
    OPEN_OBJECT = '{',
    CLOSE_OBJECT = '}',

    //array tokens
    OPEN_ARRAY = '[',
    CLOSE_ARRAY = ']',
    
    //'format' tokens
    PAIR = ':',
    NEW_DATA = ',',

    QUOTE = '"',
    ENDOFFILE = '\0'
} TokenType;

typedef struct Token{
    String* data;
    TokenType tokenType;
} Token;

Token* CreateToken(const char* data, TokenType tokenType);
void FreeToken(Token**);

#endif
