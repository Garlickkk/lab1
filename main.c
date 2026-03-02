#include "vector.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Прототипы функций для меню
void menu_int(void);
void menu_double(void);
Vector* create_int_vector_interactive(void);
Vector* create_double_vector_interactive(void);
void fill_vector_auto(Vector* v);
void fill_vector_manual(Vector* v);

// Безопасное чтение, если пользователь вводит не число, заново просит его ввести
static int safe_scan_int(int* out)
{
    if (scanf("%d", out) != 1)
    {
        // очистка буфера
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
    return 1;
}

// Безопасное чтение (аналогично)
static int safe_scan_double(double* out)
{
    if (scanf("%lf", out) != 1)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
    return 1;
}


Vector* g_int_v1 = NULL;
Vector* g_int_v2 = NULL;
Vector* g_double_v1 = NULL;
Vector* g_double_v2 = NULL;



int main(void)
{
    srand(time(NULL));

    int choice;


    do
    {
        printf("\n===================================\n");
        printf("   ПОЛИМОРФНЫЙ ВЕКТОР (ВАРИАНТ 1)\n");
        printf("===================================\n");
        printf("1. Работа с целыми числами (int)\n");
        printf("2. Работа с вещественными числами (double)\n");
        printf("3. Запустить все тесты\n");
        printf("0. Выход\n");
        printf("Выбор: ");

        if (!safe_scan_int(&choice))
        {
            printf("Неверный ввод!\n");
            continue;
        }

        switch(choice)
        {
            case 1:
                menu_int();
                break;
            case 2:
                menu_double();
                break;
            case 3:
                RunAllTests();
                break;
            case 0:
                printf("До свидания!\n");
                break;
            default:
                printf("Неверный выбор!\n");
        }
    } while(choice != 0);


    if (g_int_v1) VectorDestroy(g_int_v1);
    if (g_int_v2) VectorDestroy(g_int_v2);
    if (g_double_v1) VectorDestroy(g_double_v1);
    if (g_double_v2) VectorDestroy(g_double_v2);

    return 0;
}

//INT

void menu_int(void)
{
    int choice;



    do {
        printf("\n--- ЦЕЛЫЕ ЧИСЛА ---\n");
        printf("Текущие векторы:\n");
        printf("V1: ");
        if (g_int_v1) print_vector(g_int_v1); else printf("NULL");
        printf("\nV2: ");
        if (g_int_v2) print_vector(g_int_v2); else printf("NULL");
        printf("\n\n");

        printf("1. Создать новый вектор V1\n");
        printf("2. Создать новый вектор V2\n");
        printf("3. Заполнить векторы вручную\n");
        printf("4. Заполнить векторы автоматически\n");
        printf("5. Выполнить векторное сложение (V1 + V2)\n");
        printf("6. Вычислить скалярное произведение (V1 · V2)\n");
        printf("7. Показать векторы\n");
        printf("8. Назад\n");
        printf("Выбор: ");

        if (!safe_scan_int(&choice))
        {
            printf("Неверный ввод!\n");
            continue;
        }

        switch(choice)
        {
            case 1:
                if (g_int_v1) VectorDestroy(g_int_v1);
                g_int_v1 = create_int_vector_interactive();
                break;
            case 2:
                if (g_int_v2) VectorDestroy(g_int_v2);
                g_int_v2 = create_int_vector_interactive();
                break;
            case 3:
                if (g_int_v1 && g_int_v2) {
                    printf("Заполнение V1:\n");
                    fill_vector_manual(g_int_v1);
                    printf("Заполнение V2:\n");
                    fill_vector_manual(g_int_v2);
                } else {
                    printf("Сначала создайте оба вектора!\n");
                }
                break;
            case 4:
                if (g_int_v1 && g_int_v2) {
                    fill_vector_auto(g_int_v1);
                    fill_vector_auto(g_int_v2);
                    printf("Векторы заполнены случайными числами\n");
                } else {
                    printf("Сначала создайте оба вектора!\n");
                }
                break;
            case 5:
                if (g_int_v1 && g_int_v2) {
                    Vector* result = VectorAdd(g_int_v1, g_int_v2);
                    if (result) {
                        printf("Результат сложения: ");
                        print_vector(result);
                        printf("\n");
                        VectorDestroy(result);
                    }
                } else {
                    printf("Сначала создайте оба вектора!\n");
                }
                break;
            case 6:
                if (g_int_v1 && g_int_v2) {
                    int result;
                    VectorDot(g_int_v1, g_int_v2, &result);
                    printf("Скалярное произведение: %d\n", result);
                } else {
                    printf("Сначала создайте оба вектора!\n");
                }
                break;
            case 7:
                printf("V1: ");
                if (g_int_v1) print_vector(g_int_v1); else printf("NULL");
                printf("\nV2: ");
                if (g_int_v2) print_vector(g_int_v2); else printf("NULL");
                printf("\n");
                break;
        }
    } while(choice != 8);
}

//DOUBLE

void menu_double(void)
{
    int choice;

    do {
        printf("\n--- ВЕЩЕСТВЕННЫЕ ЧИСЛА (double) ---\n");
        printf("Текущие векторы:\n");
        printf("V1: ");
        if (g_double_v1) print_vector(g_double_v1); else printf("NULL");
        printf("\nV2: ");
        if (g_double_v2) print_vector(g_double_v2); else printf("NULL");
        printf("\n\n");

        printf("1. Создать новый вектор V1 (double)\n");
        printf("2. Создать новый вектор V2 (double)\n");
        printf("3. Заполнить векторы вручную\n");
        printf("4. Заполнить векторы автоматически\n");
        printf("5. Выполнить векторное сложение (V1 + V2)\n");
        printf("6. Вычислить скалярное произведение (V1 · V2)\n");
        printf("7. Показать векторы\n");
        printf("8. Назад\n");
        printf("Выбор: ");

        if (!safe_scan_int(&choice))
        {
            printf("Неверный ввод!\n");
            continue;
        }

        switch(choice)
        {
            case 1:
                if (g_double_v1) VectorDestroy(g_double_v1);
                g_double_v1 = create_double_vector_interactive();
                break;
            case 2:
                if (g_double_v2) VectorDestroy(g_double_v2);
                g_double_v2 = create_double_vector_interactive();
                break;
            case 3:
                if (g_double_v1 && g_double_v2) {
                    printf("Заполнение V1:\n");
                    fill_vector_manual(g_double_v1);
                    printf("Заполнение V2:\n");
                    fill_vector_manual(g_double_v2);
                } else {
                    printf("Сначала создайте оба вектора!\n");
                }
                break;
            case 4:
                if (g_double_v1 && g_double_v2) {
                    fill_vector_auto(g_double_v1);
                    fill_vector_auto(g_double_v2);
                    printf("Векторы заполнены случайными числами\n");
                } else {
                    printf("Сначала создайте оба вектора!\n");
                }
                break;
            case 5:
                if (g_double_v1 && g_double_v2) {
                    Vector* result = VectorAdd(g_double_v1, g_double_v2);
                    if (result) {
                        printf("Результат сложения: ");
                        print_vector(result);
                        printf("\n");
                        VectorDestroy(result);
                    }
                } else {
                    printf("Сначала создайте оба вектора!\n");
                }
                break;
            case 6:
                if (g_double_v1 && g_double_v2) {
                    double result;
                    VectorDot(g_double_v1, g_double_v2, &result);
                    printf("Скалярное произведение: %.2f\n", result);
                } else {
                    printf("Сначала создайте оба вектора!\n");
                }
                break;
            case 7:
                printf("V1: ");
                if (g_double_v1) print_vector(g_double_v1); else printf("NULL");
                printf("\nV2: ");
                if (g_double_v2) print_vector(g_double_v2); else printf("NULL");
                printf("\n");
                break;
        }
    } while(choice != 8);
}


Vector* create_int_vector_interactive(void) // создание нового вектора int
{
    int size;
    printf("Введите размер вектора: ");
    if (!safe_scan_int(&size))
    {
        printf("Неверный ввод!\n");
        return NULL;
    }

    if (size <= 0)
    {
        printf("Размер должен быть положительным!\n");
        return NULL;
    }

    Vector* v = VectorCreate(size, GetIntFieldInfo());
    if (v)
    {
        printf("Вектор создан на %d элементов. Теперь заполните его.\n", size);
    }
    return v;
}

Vector* create_double_vector_interactive(void) // создание нового вектора double
{
    int size;
    printf("Введите размер вектора: ");
    if (!safe_scan_int(&size))
    {
        printf("Неверный ввод!\n");
        return NULL;
    }

    if (size <= 0)
    {
        printf("Размер должен быть положительным!\n");
        return NULL;
    }

    Vector* v = VectorCreate(size, GetDoubleFieldInfo());
    if (v)
    {
        printf("Вектор создан на %d элементов. Теперь заполните его.\n", size);
    }
    return v;
}

void fill_vector_manual(Vector* v)
{
    if (v == NULL) return;

    printf("Введите %zu элементов:\n", v->size);

    void* temp = malloc(v->type->size);
    for (size_t i = 0; i < v->size; i++)
    {
        int success = 0;
        while (!success)
            {
            printf("[%zu]: ", i);
            success = v->type->scan(temp);
            if (!success)
                {
                printf("Неверный ввод, попробуйте еще раз.\n");
            }
        }
        VectorSet(v, i, temp);
    }

    free(temp);
}

void fill_vector_auto(Vector* v)
{
    if (v == NULL) return;

    void* temp = malloc(v->type->size);
    for (size_t i = 0; i < v->size; i++)
    {
        v->type->random(temp);
        VectorSet(v, i, temp);
    }
    free(temp);
}


