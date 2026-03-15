#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// create/destroy

Vector* VectorCreate(size_t size, FieldInfo* type)
{
    if (type == NULL)
        return NULL;

    Vector* vector = malloc(sizeof(Vector));
    if (!vector)
        return NULL;

    // Фиксированный размер для вектора
    if (size > 0 && size > (size_t)-1 / type->size)
    {
        free(vector);
        return NULL;
    }
    vector->data = malloc(size * type->size);
    if (!vector->data && size > 0)
    {
        free(vector);
        return NULL;
    }

    vector->size = size;
    vector->type = type;

    return vector;
}

void VectorDestroy(Vector* vector)
{
    if (!vector)
        return;

    free(vector->data);
    free(vector);
}

// get/set

void* VectorGet(const Vector* vector, size_t index) // показывает, где лежит элемент
{
    if (!vector || index >= vector->size)
        return NULL;

    return (char*)vector->data + index * vector->type->size; // возвращает адрес нужного элемента
    // vector->type->size кол-во байт в 1-м элементе
    // vector->data - адрес 1-го эл
    // для побайтового смещения, index * размер_элемента = смещение в байтах
    // (char*) нужен для побайтовой арифметики, т.к. у void* нет размерности
}

void VectorSet(Vector* vector, size_t index, const void* value) // кладет значение в нужное место
{
    if (!vector || !value || index >= vector->size)
        return;

    void* dest = (char*)vector->data + index * vector->type->size;
    memcpy(dest, value, vector->type->size); // куда откуда сколько байт
}

void VectorAdd(const Vector* v1, const Vector* v2, Vector* result)
{
    if (!v1 || !v2 || !result) // проверка существования векторов
        return;

    if (v1->type != v2->type || v1->type != result->type)
        return;

    if (v1->size != v2->size || v1->size != result->size)
        return;

    for (size_t i = 0; i < v1->size; i++)
    {
        const void* a = VectorGet(v1, i);
        const void* b = VectorGet(v2, i);
        void* dest = VectorGet(result, i);

        v1->type->add(a, b, dest);
    }
}

// dot(скалярное произведение)

void VectorDot(const Vector* v1, const Vector* v2, void* result)
{
    if (!v1 || !v2 || !result)
        return;

    if (v1->type != v2->type)
        return;

    if (v1->size != v2->size)
        return;

    // result = 0
    memset(result, 0, v1->type->size);

    void* temp = malloc(v1->type->size);
    if (!temp) return;

    for (size_t i = 0; i < v1->size; i++)
    {
        const void* a = VectorGet(v1, i);
        const void* b = VectorGet(v2, i);

        v1->type->mul(a, b, temp);
        v1->type->add(result, temp, result);
    }

    free(temp);
}

void print_vector(const Vector* v)
{
    if (v == NULL)
    {
        printf("NULL");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v->size; i++)
    {
        const void* elem = VectorGet(v, i);

        v->type->print(elem);

        if (i < v->size - 1) printf(", ");
    }
    printf("]");
}
