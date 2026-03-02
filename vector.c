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

void* VectorGet(Vector* vector, size_t index) // показывает, где лежит элемент
{
    if (!vector || index >= vector->size)
        return NULL;

    return (char*)vector->data + index * vector->type->size; // возвращает адрес нужного элемента(указатель на элемент с индексом index: (char*))
    // vector->type->size кол-во байт в 1-м элементе
    // vector->data - адрес 1-го эл
    // для побайтового смещения, index * размер_элемента = смещение в байтах
}
// объяснить зачем char
void VectorSet(Vector* vector, size_t index, void* value) // кладет значение в нужное место
{
    if (!vector || !value || index >= vector->size)
        return;

    void* dest = (char*)vector->data + index * vector->type->size;
    memcpy(dest, value, vector->type->size); // куда откуда сколько байт
}

// vector add

Vector* VectorAdd(Vector* v1, Vector* v2)
{
    if (!v1 || !v2) // не существование вектора
        return NULL;

    if (v1->type != v2->type)
        return NULL;

    if (v1->size != v2->size)
        return NULL;

    Vector* result = VectorCreate(v1->size, v1->type);
    if (!result)
        return NULL;

    for (size_t i = 0; i < v1->size; i++)
    {
        void* a = VectorGet(v1, i);
        void* b = VectorGet(v2, i);
        void* dest = VectorGet(result, i);

        v1->type->add(a, b, dest);
    }

    return result;
}

// dot(скалярное произведение)

void VectorDot(Vector* v1, Vector* v2, void* result)
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
        void* a = VectorGet(v1, i);
        void* b = VectorGet(v2, i);

        v1->type->mul(a, b, temp);
        v1->type->add(result, temp, result);
    }

    free(temp);
}


void print_vector(Vector* v)
{
    if (v == NULL)
    {
        printf("NULL");
        return;
    }

    printf("[");
    for (size_t i = 0; i < v->size; i++)
    {
        void* elem = VectorGet(v, i);

        v->type->print(elem);

        if (i < v->size - 1) printf(", ");
    }
    printf("]");
}