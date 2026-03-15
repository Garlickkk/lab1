#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stddef.h>

typedef struct FieldInfo
{
    size_t size;
    void (*add)(const void* a, const void* b, void* result);
    void (*mul)(const void* a, const void* b, void* result);
    void (*print)(const void* a);
    int (*scan)(void* a);
    void (*random)(void* a);
} FieldInfo;

FieldInfo* GetIntFieldInfo();
FieldInfo* GetDoubleFieldInfo();

#endif
