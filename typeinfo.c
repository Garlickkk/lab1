#include "typeinfo.h"
#include <stdio.h>
#include <stdlib.h>

//вспомогательные функции

static int safe_scan_int(int* out)
{
    if (scanf("%d", out) != 1)
    {
        int c;
        while ((c = getchar()) != '\n');
        return 0;
    }
    return 1;
}

static int safe_scan_double(double* out)
{
    if (scanf("%lf", out) != 1)
    {
        int c;
        while ((c = getchar()) != '\n');
        return 0;
    }
    return 1;
}

//INT

static FieldInfo* INT_FIELD_INFO = NULL;

static void int_add(const void* a, const void* b, void* result)
{
    const int* pa = (const int*)a;
    const int* pb = (const int*)b;
    int* pr = (int*)result;

    *pr = (*pa) + (*pb);
}

static void int_mul(const void* a, const void* b, void* result)
{
    const int* pa = (const int*)a;
    const int* pb = (const int*)b;
    int* pr = (int*)result;

    *pr = (*pa) * (*pb);
}

static void int_print(const void* a)
{
    const int* pa = (const int*)a;
    printf("%d", *pa);
}

static int int_scan(void* a)
{
    return safe_scan_int((int*)a);
}

static void int_random(void* a)
{
    *(int*)a = rand() % 21 - 10;  // от -10 до 10
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
        INT_FIELD_INFO->print = int_print;
        INT_FIELD_INFO->scan = int_scan;
        INT_FIELD_INFO->random = int_random;
    }
    return INT_FIELD_INFO;
}

//DOUBLE

static FieldInfo* DOUBLE_FIELD_INFO = NULL;

static void double_add(const void* a, const void* b, void* result)
{
    const double* pa = (const double*)a;
    const double* pb = (const double*)b;
    double* pr = (double*)result;

    *pr = (*pa) + (*pb);
}

static void double_mul(const void* a, const void* b, void* result)
{
    const double* pa = (const double*)a;
    const double* pb = (const double*)b;
    double* pr = (double*)result;

    *pr = (*pa) * (*pb);
}

static void double_print(const void* a)
{
    const double* pa = (const double*)a;
    printf("%.2f", *pa);
}

static int double_scan(void* a)
{
    return safe_scan_double((double*)a);
}

static void double_random(void* a)
{
    *(double*)a = (rand() % 2001 - 1000) / 100.0;  // от -10.00 до 10.00
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
        DOUBLE_FIELD_INFO->print = double_print;
        DOUBLE_FIELD_INFO->scan = double_scan;
        DOUBLE_FIELD_INFO->random = double_random;
    }
    return DOUBLE_FIELD_INFO;
}
