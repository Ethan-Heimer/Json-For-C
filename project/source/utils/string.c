#include "utils/string.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

String* CreateString(){
    String* str = (String*)malloc(sizeof(String));
    if(str == NULL)
        return NULL;
    
    char* buffer = (char*)malloc(sizeof(char));
    if(buffer == NULL){
        free(str);
        return NULL;
    }

    str->string = buffer;
    str->string[0] = '\0';

    str->length = 1;

    return str;
}

String* CreateStringWith(const char* string){
    String* str = (String*)malloc(sizeof(String));
    if(str == NULL)
        return NULL;
   
    int length = strlen(string) + 1;
    char* buffer = (char*)calloc(length, sizeof(char));
    if(buffer == NULL){
        free(str);
        return NULL;
    }

    memcpy(buffer, string, length);

    str->string = buffer;
    str->length = length;

    return str; 
}

String* CreateNormStringWith(const char* string){
    String* str = (String*)malloc(sizeof(String));
    if(str == NULL)
        return NULL;
   
    //remove white space
    bool skipSpace = false;
    int paramLength = strlen(string) + 1;
    char* normBuffer = (char*)calloc(paramLength, sizeof(char));
    if(normBuffer == NULL){
        free(str);
        return NULL;
    }
  
    char c;
    int normIndex = 0; 
    for(int i = 0; i < paramLength-1; i++){
        c = string[i];
        if(c == '"')
            skipSpace = !skipSpace;

        if(!isspace(c) || skipSpace){
            normBuffer[normIndex] = c;
            normIndex++; 
        }
    }

    normBuffer[normIndex] = '\0';
    int newLength = normIndex + 1;

    char* tempBuf = realloc(normBuffer, sizeof(char) * newLength);
    if(tempBuf == NULL){
        free(normBuffer);
        return NULL;
    } else {
        normBuffer = tempBuf;
    }

    str->string = normBuffer;
    str->length = newLength;

    return str; 
}

void AppendString(String* string, const char* appendix){
    int currentSize = string->length;
    int appendixSize = strlen(appendix);

    int newSize = currentSize + appendixSize;

    char* buffer = (char*)realloc(string->string, newSize * sizeof(char));
    if(buffer == NULL){
        perror("String cannot be appended");
        free(buffer);
        return;
    }

    //strcpy(buffer, string->string);
    strcat(buffer, appendix);

    //free(string->string);

    string->string = buffer;
    string->length = newSize;
}

void AppendNumber(String* string, int number){
    char str[20];
    sprintf(str, "%d", number);

    AppendString(string, str);
}

void AppendChar(String* string, char c){
    int newSize = string->length + 1;

    char* newString = (char*)realloc(string->string, newSize * sizeof(char));
    if(newString == NULL){
        perror("String cannot be appended");
        free(string->string);
        return;
    }
 
    //add char
    newString[newSize-2] = c;
    newString[newSize-1] = '\0';

    string->string = newString;
    string->length = newSize;
}

char GetCharacter(String* string, unsigned int index){
    if(index > string->length-1)
        return '\0';

    return string->string[index];
}

void ClearString(String* string){
    free(string->string);
    
    char* buffer = (char*)malloc(sizeof(char));
    if(buffer == NULL){
        string->string = NULL;
        string->length = 0;

        perror("String did not clear correctly");
        return;
    }

    buffer[0] = '\0';

    string->string = buffer;
    string->length = 1;
}

void CopyString(String* dest, String* src){
    ClearString(dest);
    AppendString(dest, src->string);
}

void DeleteString(String** string){
    if(string == NULL)
        return;

    free((*string)->string);
    free(*string);

    *string = NULL;
}

bool SameStringValue(String* one, const char* value){
    if(one == NULL)
        return false;

    return strcmp(one->string, value) == 0;
}
