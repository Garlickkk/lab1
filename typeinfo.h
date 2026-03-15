#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stddef.h>

typedef struct FieldInfo
{
    size_t size;

    void (*add)(void* a, void* b, void* result);
    void (*mul)(void* a, void* b, void* result);
} FieldInfo;

FieldInfo* GetIntFieldInfo();
FieldInfo* GetDoubleFieldInfo();

#endif