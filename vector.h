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
void print_vector(Vector* vector);
void* VectorGet(Vector* vector, size_t index);
void VectorSet(Vector* vector, size_t index, void* value);
Vector* VectorAdd(Vector* v1, Vector* v2);
void VectorDot(Vector* v1, Vector* v2, void* result);

void print_vector(Vector* v);
#endif
