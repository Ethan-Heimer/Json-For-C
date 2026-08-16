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

typedef enum TokenValueType{
    NO_VALUE = 0,
    STRING_VALUE,
    INT_VALUE,
    FLOAT_VALUE,
    NULL_VALUE,
    BOOL_VALUE,
} TokenValueType;

typedef struct Token{
    String* data;
    TokenType tokenType;
    TokenValueType valueType;
} Token;

Token* CreateToken(const char* data, TokenType tokenType, TokenValueType valueType);
void FreeToken(Token**);

#endif
