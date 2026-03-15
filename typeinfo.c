#include "typeinfo.h"
#include <stdlib.h>

/* ================= INT ================= */

static FieldInfo* INT_FIELD_INFO = NULL;

static void int_add(void* a, void* b, void* result)
{
    *(int*)result = *(int*)a + *(int*)b;
}

static void int_mul(void* a, void* b, void* result)
{
    *(int*)result = *(int*)a * *(int*)b;
}

FieldInfo* GetIntFieldInfo()
{
    if (INT_FIELD_INFO == NULL)
    {
        INT_FIELD_INFO = malloc(sizeof(FieldInfo));
        if (!INT_FIELD_INFO) return NULL;
        INT_FIELD_INFO->size = sizeof(int);
        INT_FIELD_INFO->add = int_add;
        INT_FIELD_INFO->mul = int_mul;
    }
    return INT_FIELD_INFO;
}

/* ================= DOUBLE ================= */

static FieldInfo* DOUBLE_FIELD_INFO = NULL;

static void double_add(void* a, void* b, void* result)
{
    *(double*)result = *(double*)a + *(double*)b;
}

static void double_mul(void* a, void* b, void* result)
{
    *(double*)result = *(double*)a * *(double*)b;
}

FieldInfo* GetDoubleFieldInfo()
{
    if (DOUBLE_FIELD_INFO == NULL)
    {
        DOUBLE_FIELD_INFO = malloc(sizeof(FieldInfo));
        if (!DOUBLE_FIELD_INFO) return NULL;
        DOUBLE_FIELD_INFO->size = sizeof(double);
        DOUBLE_FIELD_INFO->add = double_add;
        DOUBLE_FIELD_INFO->mul = double_mul;
    }
    return DOUBLE_FIELD_INFO;
}