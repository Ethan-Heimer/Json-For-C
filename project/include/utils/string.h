#ifndef DYN_STRING_H
#define DYN_STRING_H

#include <stdbool.h>

typedef struct String{
    char* string;
    int length;
} String;

String* CreateString();

void AppendString(String*, const char* appendix);
void AppendChar(String*, char);
void AppendNumber(String*, int);

char GetCharacter(String*, unsigned int index);

void ClearString(String*);
void CopyString(String* dest, String* src);

void DeleteString(String**);

bool SameStringValue(String* string, const char* value);

#endif
