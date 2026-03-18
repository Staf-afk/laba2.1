#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "student.h"
#include "teacher.h"
#include "funcs.h"

// Глобальные счетчики для статистики
extern int testsPassed;
extern int testsFailed;
extern int testsTotal;

// Макросы для запуска и проверок
#define TEST(name) void test##name(void)
#define RUN_TEST(name) do { \
    printf("  [ЗАПУСК] %s... ", #name); \
    test##name(); \
} while(0)

#define ASSERT_TRUE(cond) do { \
    if (!(cond)) { \
        printf("ПРОВАЛ (Условие не выполнено: %s)\n", #cond); \
        testsFailed++; \
        return; \
    } \
} while(0)

#define ASSERT_FALSE(cond) ASSERT_TRUE(!(cond))
#define ASSERT_NULL(ptr) ASSERT_TRUE((ptr) == NULL)
#define ASSERT_NOT_NULL(ptr) ASSERT_TRUE((ptr) != NULL)

#define ASSERT_EQ_INT(a, b) do { \
    if ((a) != (b)) { \
        printf("ПРОВАЛ (Ожидалось %d, получено %d)\n", (b), (a)); \
        testsFailed++; \
        return; \
    } \
} while(0)

#define ASSERT_EQ_STR(a, b) do { \
    if (strcmp((a), (b)) != 0) { \
        printf("ПРОВАЛ (Ожидалось '%s', получено '%s')\n", (b), (a)); \
        testsFailed++; \
        return; \
    } \
} while(0)

#define TEST_PASS() do { \
    printf("УСПЕХ\n"); \
    testsPassed++; \
} while(0)

// Инициализация и отчет
#define TEST_INIT() do { \
    printf("\n=== ЗАПУСК ТЕСТИРОВАНИЯ ===\n\n"); \
    testsPassed = 0; \
    testsFailed = 0; \
    testsTotal = 0; \
} while(0)

#define TEST_REPORT() do { \
    testsTotal = testsPassed + testsFailed; \
    printf("\n=== ОТЧЕТ ПО ТЕСТАМ ===\n"); \
    printf("Всего тестов:  %d\n", testsTotal); \
    printf("Пройдено:      %d\n", testsPassed); \
    printf("Провалено:     %d\n", testsFailed); \
    if (testsFailed == 0) { \
        printf("\n[OK] Все тесты пройдены успешно!\n"); \
    } else { \
        printf("\n[ERROR] Обнаружены ошибки в коде!\n"); \
    } \
} while(0)

// Объявление главной функции тестов
void runAllTests(void);

#endif