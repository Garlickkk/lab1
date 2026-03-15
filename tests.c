#include <stdio.h>
#include <assert.h> // для cравнения результата
#include <math.h>
#include "vector.h"
#include "typeinfo.h"



static Vector* CreateIntVectorFromArray(int* arr, size_t n)
{
    Vector* v = VectorCreate(n, GetIntFieldInfo());
    for (size_t i = 0; i < n; i++)
        VectorSet(v, i, &arr[i]);
    return v;
}

static Vector* CreateDoubleVectorFromArray(double* arr, size_t n)
{
    Vector* v = VectorCreate(n, GetDoubleFieldInfo());
    for (size_t i = 0; i < n; i++)
        VectorSet(v, i, &arr[i]);
    return v;
}

// ТЕСТЫ INT

static void TestIntVectorAdd()
{
    printf("Test int vector");

    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};

    Vector* v1 = CreateIntVectorFromArray(a, 3);
    Vector* v2 = CreateIntVectorFromArray(b, 3);

    Vector* sum = VectorAdd(v1, v2);

    assert(sum != NULL);
    assert(*(int*)VectorGet(sum, 0) == 5);
    assert(*(int*)VectorGet(sum, 1) == 7);
    assert(*(int*)VectorGet(sum, 2) == 9);

    VectorDestroy(v1);
    VectorDestroy(v2);
    VectorDestroy(sum);

    printf("OK\n");
}

static void TestIntDotProduct() {
    printf("Test int dot product");

    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};

    Vector* v1 = CreateIntVectorFromArray(a, 3);
    Vector* v2 = CreateIntVectorFromArray(b, 3);

    int result = 0;
    VectorDot(v1, v2, &result);

    assert(result == 32);

    VectorDestroy(v1);
    VectorDestroy(v2);

    printf("OK\n");
}

// ТЕСТЫ DOUBLE

static void TestDoubleVectorAdd() {
    printf("Test double vector");

    double a[] = {1.0, 2.0, 3.0};
    double b[] = {0.5, 1.5, 2.5};

    Vector* v1 = CreateDoubleVectorFromArray(a, 3);
    Vector* v2 = CreateDoubleVectorFromArray(b, 3);

    Vector* sum = VectorAdd(v1, v2);

    assert(sum != NULL);
    assert(fabs(*(double*)VectorGet(sum, 0) - 1.5) < 1e-9);
    assert(fabs(*(double*)VectorGet(sum, 1) - 3.5) < 1e-9);
    assert(fabs(*(double*)VectorGet(sum, 2) - 5.5) < 1e-9);

    VectorDestroy(v1);
    VectorDestroy(v2);
    VectorDestroy(sum);

    printf("OK\n");
}

static void TestDoubleDotProduct()
{
    printf("Test double dot product");

    double a[] = {1.0, 2.0, 3.0};
    double b[] = {4.0, 5.0, 6.0};

    Vector* v1 = CreateDoubleVectorFromArray(a, 3);
    Vector* v2 = CreateDoubleVectorFromArray(b, 3);

    double result = 0.0;
    VectorDot(v1, v2, &result);

    assert(fabs(result - 32.0) < 1e-9);

    VectorDestroy(v1);
    VectorDestroy(v2);

    printf("OK\n");
}

// ТЕСТЫ ОШИБОК

static void TestDifferentTypes() {
    printf("Test error - different types");

    int a[] = {1, 2};
    double b[] = {1.0, 2.0};

    Vector* v1 = CreateIntVectorFromArray(a, 2);
    Vector* v2 = CreateDoubleVectorFromArray(b, 2);

    Vector* result = VectorAdd(v1, v2);

    assert(result == NULL);

    VectorDestroy(v1);
    VectorDestroy(v2);

    printf("OK\n");
}

static void TestDifferentSizes() {
    printf("Test error - different sizes");

    int a[] = {1, 2};
    int b[] = {1, 2, 3};

    Vector* v1 = CreateIntVectorFromArray(a, 2);
    Vector* v2 = CreateIntVectorFromArray(b, 3);

    Vector* result = VectorAdd(v1, v2);

    assert(result == NULL);

    VectorDestroy(v1);
    VectorDestroy(v2);

    printf("OK\n");
}

static void TestNullVectors() {
    printf("Test error - NULL vectors");

    Vector* result = VectorAdd(NULL, NULL);

    assert(result == NULL);

    printf("OK\n");
}

/* ================= ЗАПУСК ВСЕХ ================= */

void RunAllTests() {
    printf("\n===================================\n");
    printf("      ЗАПУСК  ТЕСТОВ\n");
    printf("===================================\n\n");

    TestIntVectorAdd();
    TestIntDotProduct();
    TestDoubleVectorAdd();
    TestDoubleDotProduct();
    TestDifferentTypes();
    TestDifferentSizes();
    TestNullVectors();

    printf("\n===================================\n");
    printf("      ТЕСТЫ ПРОЙДЕНЫ!\n");
    printf("===================================\n\n");
}