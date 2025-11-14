#ifndef JSON_TREE_H
#define JSON_TREE_H

#include <stdbool.h>
#include "utils/string.h"

typedef enum JsonTreeType{
    ARRAY,
    OBJECT
} JsonTreeType;

typedef struct Json{
    String* key;
    String* data;

    struct Json** children;
    int childLength;
} Json;

Json* NewJson();
void DeleteJson(Json** tree);

void AddJsonChild(Json* parent, Json* child);

#endif
