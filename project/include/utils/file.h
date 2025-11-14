#ifndef FILE_H
#define FILE_H

#include "utils/string.h"

String* GetFile(const char* path);
String* GetNormalizedFile(const char* path);

#endif
