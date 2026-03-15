#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include "typeinfo.h"

typedef struct Vector
{
    void* data;           // указатель на массив эл
    size_t size;          // количество элементов
    FieldInfo* type;      // инфо о типе
} Vector;

Vector* VectorCreate(size_t size, FieldInfo* type);
void VectorDestroy(Vector* vector);
void print_vector(const Vector* vector);
void* VectorGet(const Vector* vector, size_t index);
void VectorSet(Vector* vector, size_t index, const void* value);
void VectorAdd(const Vector* v1, const Vector* v2, Vector* result);
void VectorDot(const Vector* v1, const Vector* v2, void* result);

#endif
