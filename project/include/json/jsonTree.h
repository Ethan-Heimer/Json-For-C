#ifndef JSON_TREE_H
#define JSON_TREE_H

#include <stdbool.h>
#include "json/json.h"

typedef enum JsonTreeType{
    T_ARRAY,
    T_OBJECT
} JsonTreeType;

Json* NewJson();

void DeleteJson(Json** tree);
void AddJsonChild(Json* parent, Json* child);

#endif
