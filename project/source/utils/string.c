#include "utils/string.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
