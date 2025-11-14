#include "utils/file.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

String* GetFile(const char* path){
    FILE* file = fopen(path, "r");
    
    if(file == NULL)
    {
        perror("FILE NOT FOUND");
        return NULL;
    }

    String* buffer = CreateString();

    char c;
    while((c = fgetc(file)) != EOF){
        AppendChar(buffer, c);
    }

    fclose(file);
    return buffer;
}

String* GetNormalizedFile(const char* path){
    FILE* file = fopen(path, "r");
    
    if(file == NULL)
    {
        perror("FILE NOT FOUND");
        return NULL;
    }
    
    bool skipSpace = false;
    String* buffer = CreateString();
    
    char c;
    while((c = fgetc(file)) != EOF){
        //this is to preserve data between quotes
        if(c == '"')
            skipSpace = !skipSpace;

        if(!isspace(c) || skipSpace)
            AppendChar(buffer, c);
    }
    
    fclose(file);
    return buffer;
}
