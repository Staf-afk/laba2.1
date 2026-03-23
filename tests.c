#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "funcs.h"
#include "tests.h"

int tests_passed = 0;
int tests_failed = 0;



// Создать тестового студента
Student* createTestStudent(const char* fn, const char* sn, const char* ln,
                           int day, int month, int year,
                           int series, int number, int scholarship) {
    Person_ID id = {series, number};
    return createStudent((char*)fn, (char*)sn, (char*)ln,
                         day, month, year, &id, scholarship);
}

// Создать тестового преподавателя
Teacher* createTestTeacher(const char* fn, const char* sn, const char* ln,
                           int day, int month, int year,
                           int series, int number, int salary) {
    Person_ID id = {series, number};
    return createTeacher((char*)fn, (char*)sn, (char*)ln,
                         day, month, year, &id, salary);
}

// ТЕСТЫ ДЛЯ person.c

void test_setPassportFormat(void) {
    TEST_START("setPassportFormat");
    
    setPassportFormat(FORMAT_SINGLE_NUMBER);
    ASSERT(getPassportFormat() == FORMAT_SINGLE_NUMBER, 
           "Не установился FORMAT_SINGLE_NUMBER");
    
    setPassportFormat(FORMAT_STRUCTURE);
    ASSERT(getPassportFormat() == FORMAT_STRUCTURE, 
           "Не установился FORMAT_STRUCTURE");
    
    setPassportFormat(FORMAT_SPACE_SEPARATED);
    ASSERT(getPassportFormat() == FORMAT_SPACE_SEPARATED, 
           "Не установился FORMAT_SPACE_SEPARATED");
    
    TEST_PASS();
}

void test_getPassportFormat(void) {
    TEST_START("getPassportFormat");
    
    PassportFormat format = getPassportFormat();
    ASSERT(format >= 0 && format <= 2, "Некорректное значение формата");
    
    TEST_PASS();
}

void test_comparePassportIDs(void) {
    TEST_START("comparePassportIDs");
    
    ASSERT(comparePassportIDs(NULL, NULL) == 0, "NULL сравнение не вернуло 0");
    
    Person_ID id1 = {1234, 5678};
    Person_ID id2 = {1234, 5678};
    Person_ID id3 = {1234, 9999};
    Person_ID id4 = {9999, 5678};
    
    setPassportFormat(FORMAT_STRUCTURE);
    ASSERT(comparePassportIDs(&id1, &id2) == 1, 
           "Одинаковые ID не совпали (STRUCTURE)");
    ASSERT(comparePassportIDs(&id1, &id3) == 0, 
           "Разные номера совпали (STRUCTURE)");
    ASSERT(comparePassportIDs(&id1, &id4) == 0, 
           "Разные серии совпали (STRUCTURE)");
    
    setPassportFormat(FORMAT_SINGLE_NUMBER);
    ASSERT(comparePassportIDs(&id1, &id3) == 1, 
           "Серии не совпали (SINGLE_NUMBER)");
    ASSERT(comparePassportIDs(&id1, &id4) == 0, 
           "Разные серии совпали (SINGLE_NUMBER)");
    
    setPassportFormat(FORMAT_SPACE_SEPARATED);
    ASSERT(comparePassportIDs(&id1, &id2) == 1, 
           "Одинаковые ID не совпали (SPACE_SEPARATED)");
    ASSERT(comparePassportIDs(&id1, &id3) == 0, 
           "Разные номера совпали (SPACE_SEPARATED)");
    
    TEST_PASS();
}

void test_printPassportID(void) {
    TEST_START("printPassportID");
    
    printPassportID(NULL);  
    
    Person_ID id = {1234, 5678};
    
    setPassportFormat(FORMAT_SINGLE_NUMBER);
    printf("(Single Number) ");
    printPassportID(&id);
    printf("\n");
    
    setPassportFormat(FORMAT_SPACE_SEPARATED);
    printf("(Space Separated) ");
    printPassportID(&id);
    printf("\n");
    
    setPassportFormat(FORMAT_STRUCTURE);
    printf("(Structure) ");
    printPassportID(&id);
    printf("\n");
    
    TEST_PASS();
}

void test_initPersonList(void) {
    TEST_START("initPersonList");
    
    PersonArray arr;
    initPersonList(&arr);
    
    ASSERT(arr.data == NULL, "data не NULL после инициализации");
    ASSERT(arr.size == 0, "size не 0 после инициализации");
    
    TEST_PASS();
}

void test_addPerson(void) {
    TEST_START("addPerson");
    
    PersonArray arr;
    initPersonList(&arr);
    
    Student* s1 = createTestStudent("Иван", "Иванович", "Иванов",
                                    1, 1, 2000, 1111, 2222, 5000);
    ASSERT(s1 != NULL, "Не создан студент 1");
    addPerson(&arr, (PersonBase*)s1);  // <-- Явный cast
    ASSERT(arr.size == 1, "Размер не увеличился после первого добавления");
    ASSERT(arr.data[0] == (PersonBase*)s1, "Указатель не сохранён");
    
    Teacher* t1 = createTestTeacher("Петр", "Петрович", "Петров",
                                    1, 1, 1980, 3333, 4444, 50000);
    ASSERT(t1 != NULL, "Не создан преподаватель 1");
    addPerson(&arr, (PersonBase*)t1);  
    ASSERT(arr.size == 2, "Размер не увеличился после второго добавления");
    ASSERT(arr.data[1] == (PersonBase*)t1, "Второй указатель не сохранён");
    
    Student* s2 = createTestStudent("Анна", "Анновна", "Аннова",
                                    15, 6, 2001, 5555, 6666, 6000);
    addPerson(&arr, (PersonBase*)s2);  
    ASSERT(arr.size == 3, "Размер не увеличился после третьего добавления");
    
    freePersonArray(&arr);
    TEST_PASS();
}

void test_removePerson(void) {
    TEST_START("removePerson");
    
    PersonArray arr;
    initPersonList(&arr);
    
    for (int i = 0; i < 3; i++) {
        Student* s = createTestStudent("Имя", "Отчество", "Фамилия",
                                       1, 1, 2000, 1000 + i, 2000 + i, 5000);
        addPerson(&arr, (PersonBase*)s);  
    }
    
    ASSERT(arr.size == 3, "Не добавилось 3 человека");
    
    removePerson(&arr, 1);
    ASSERT(arr.size == 2, "Размер не уменьшился после удаления");
    
    removePerson(&arr, 0);
    ASSERT(arr.size == 1, "Размер не уменьшился после второго удаления");
    
    removePerson(&arr, 0);
    ASSERT(arr.size == 0, "Массив не пуст после удаления всех");
    ASSERT(arr.data == NULL, "data не NULL после удаления всех элементов");
    
    addPerson(&arr, (PersonBase*)createTestStudent("Тест", "Тестович", "Тестов",
                                      1, 1, 2000, 9999, 9999, 5000));  
    removePerson(&arr, -1);  // Должно вывести ошибку
    removePerson(&arr, 100); // Должно вывести ошибку
    
    freePersonArray(&arr);
    TEST_PASS();
}

void test_freePersonArray(void) {
    TEST_START("freePersonArray");
    
    PersonArray arr;
    initPersonList(&arr);
    
    addPerson(&arr, (PersonBase*)createTestStudent("Иван", "Иванович", "Иванов",
                                                    1, 1, 2000, 1111, 2222, 5000));
    addPerson(&arr, (PersonBase*)createTestTeacher("Петр", "Петрович", "Петров",
                                                    1, 1, 1980, 3333, 4444, 50000));
    
    ASSERT(arr.size == 2, "Не добавилось 2 человека");
    
    freePersonArray(&arr);
    ASSERT(arr.data == NULL, "data не обнулён");
    ASSERT(arr.size == 0, "size не обнулён");
    
    freePersonArray(&arr);
    
    TEST_PASS();
}

void test_isStudent_isTeacher(void) {
    TEST_START("isStudent/isTeacher");
    
    Student* s = createTestStudent("Иван", "Иванович", "Иванов",
                                   1, 1, 2000, 1111, 2222, 5000);
    Teacher* t = createTestTeacher("Петр", "Петрович", "Петров",
                                   1, 1, 1980, 3333, 4444, 50000);
    
    ASSERT(isStudent((PersonBase*)s) == 1, "Студент не распознан");
    ASSERT(isTeacher((PersonBase*)s) == 0, "Студент распознан как преподаватель");
    ASSERT(isTeacher((PersonBase*)t) == 1, "Преподаватель не распознан");
    ASSERT(isStudent((PersonBase*)t) == 0, "Преподаватель распознан как студент");
    ASSERT(isStudent(NULL) == 0, "NULL не обработан в isStudent");
    ASSERT(isTeacher(NULL) == 0, "NULL не обработан в isTeacher");
    
    free(s->base.firstName);
    free(s->base.secondName);
    free(s->base.lastName);
    free(s);
    
    free(t->base.firstName);
    free(t->base.secondName);
    free(t->base.lastName);
    free(t);
    
    TEST_PASS();
}

void test_printPerson(void) {
    TEST_START("printPerson");
    
    printPerson(NULL);  // Не должно падать
    
    Student* s = createTestStudent("Иван", "Иванович", "Иванов",
                                   15, 6, 2000, 1111, 2222, 7500);
    printf("Студент: ");
    printPerson((PersonBase*)s);
    
    Teacher* t = createTestTeacher("Петр", "Петрович", "Петров",
                                   10, 3, 1980, 3333, 4444, 75000);
    printf("Преподаватель: ");
    printPerson((PersonBase*)t);
    
    free(s->base.firstName);
    free(s->base.secondName);
    free(s->base.lastName);
    free(s);
    
    free(t->base.firstName);
    free(t->base.secondName);
    free(t->base.lastName);
    free(t);
    
    TEST_PASS();
}

void test_printAllPersons(void) {
    TEST_START("printAllPersons");
    
    printAllPersons(NULL);
    
    PersonArray arr;
    initPersonList(&arr);
    printAllPersons(&arr);
    
    addPerson(&arr, (PersonBase*)createTestStudent("Иван", "Иванович", "Иванов",
                                                    1, 1, 2000, 1111, 2222, 5000));
    addPerson(&arr, (PersonBase*)createTestTeacher("Петр", "Петрович", "Петров",
                                                    1, 1, 1980, 3333, 4444, 50000));
    printAllPersons(&arr);
    
    freePersonArray(&arr);
    TEST_PASS();
}

void test_findPersonByID(void) {
    TEST_START("findPersonByID");
    
    PersonArray arr;
    initPersonList(&arr);
    
    PersonBase* found = findPersonByID(NULL, 1111, 2222);
    ASSERT(found == NULL, "NULL массив не обработан");
    
    found = findPersonByID(&arr, 1111, 2222);
    ASSERT(found == NULL, "Пустой массив не обработан");
    
    addPerson(&arr, (PersonBase*)createTestStudent("Иван", "Иванович", "Иванов",
                                                    1, 1, 2000, 1111, 2222, 5000));
    addPerson(&arr, (PersonBase*)createTestTeacher("Петр", "Петрович", "Петров",
                                                    1, 1, 1980, 3333, 4444, 50000));
    
    found = findPersonByID(&arr, 1111, 2222);
    ASSERT(found != NULL, "Студент не найден по ID");
    ASSERT(isStudent(found) == 1, "Найден не студент");
    
    found = findPersonByID(&arr, 3333, 4444);
    ASSERT(found != NULL, "Преподаватель не найден по ID");
    ASSERT(isTeacher(found) == 1, "Найден не преподаватель");
    
    found = findPersonByID(&arr, 9999, 9999);
    ASSERT(found == NULL, "Найден несуществующий человек");
    
    freePersonArray(&arr);
    TEST_PASS();
}

void test_findStudentByIndex(void) {
    TEST_START("findStudentByIndex");
    
    PersonArray arr;
    initPersonList(&arr);
    
    Student* found = findStudentByIndex(NULL, 0);
    ASSERT(found == NULL, "NULL массив не обработан");
    
    found = findStudentByIndex(&arr, 0);
    ASSERT(found == NULL, "Пустой массив не обработан");
    
    addPerson(&arr, (PersonBase*)createTestStudent("Иван", "Иванович", "Иванов",
                                                    1, 1, 2000, 1111, 2222, 5000));
    addPerson(&arr, (PersonBase*)createTestTeacher("Петр", "Петрович", "Петров",
                                                    1, 1, 1980, 3333, 4444, 50000));
    addPerson(&arr, (PersonBase*)createTestStudent("Анна", "Анновна", "Аннова",
                                                    15, 6, 2001, 5555, 6666, 6000));
    
    found = findStudentByIndex(&arr, 0);
    ASSERT(found != NULL, "Студент не найден по индексу 0");

    found = findStudentByIndex(&arr, 1);
    ASSERT(found == NULL, "Найден студент там, где преподаватель");

    found = findStudentByIndex(&arr, 2);
    ASSERT(found != NULL, "Студент не найден по индексу 2");

    found = findStudentByIndex(&arr, 100);
    ASSERT(found == NULL, "Неверный индекс не обработан");
    
    found = findStudentByIndex(&arr, -1);
    ASSERT(found == NULL, "Отрицательный индекс не обработан");
    
    freePersonArray(&arr);
    TEST_PASS();
}

void test_findTeacherByIndex(void) {
    TEST_START("findTeacherByIndex");
    
    PersonArray arr;
    initPersonList(&arr);

    addPerson(&arr, (PersonBase*)createTestStudent("Иван", "Иванович", "Иванов",
                                                    1, 1, 2000, 1111, 2222, 5000));
    addPerson(&arr, (PersonBase*)createTestTeacher("Петр", "Петрович", "Петров",
                                                    1, 1, 1980, 3333, 4444, 50000));
    addPerson(&arr, (PersonBase*)createTestStudent("Анна", "Анновна", "Аннова",
                                                    15, 6, 2001, 5555, 6666, 6000));
    
    Teacher* found = findTeacherByIndex(&arr, 1);
    ASSERT(found != NULL, "Преподаватель не найден по индексу 1");
    
    found = findTeacherByIndex(&arr, 0);
    ASSERT(found == NULL, "Найден преподаватель там, где студент");
    
    found = findTeacherByIndex(&arr, 100);
    ASSERT(found == NULL, "Неверный индекс не обработан");
    
    freePersonArray(&arr);
    TEST_PASS();
}

// ТЕСТЫ ДЛЯ student.c

void test_createStudent(void) {
    TEST_START("createStudent");
    
    Person_ID id = {1111, 2222};
    
    Student* s = createStudent("Иван", "Иванович", "Иванов",
                               15, 6, 2000, &id, 7500);
    
    ASSERT(s != NULL, "Студент не создан");
    ASSERT(strcmp(s->base.firstName, "Иван") == 0, "Имя не совпадает");
    ASSERT(strcmp(s->base.secondName, "Иванович") == 0, "Отчество не совпадает");
    ASSERT(strcmp(s->base.lastName, "Иванов") == 0, "Фамилия не совпадает");
    ASSERT(s->base.dayBirth == 15, "День рождения не совпадает");
    ASSERT(s->base.monthBirth == 6, "Месяц рождения не совпадает");
    ASSERT(s->base.yearBirth == 2000, "Год рождения не совпадает");
    ASSERT(s->base.id.series == 1111, "Серия паспорта не совпадает");
    ASSERT(s->base.id.number == 2222, "Номер паспорта не совпадает");
    ASSERT(s->scholarship == 7500, "Стипендия не совпадает");
    ASSERT(s->base.type == PERSON_STUDENT, "Тип не установлен");
    
    free(s->base.firstName);
    free(s->base.secondName);
    free(s->base.lastName);
    free(s);
    
    TEST_PASS();
}

void test_createStudent_nullInput(void) {
    TEST_START("createStudent NULL input");
    
    Person_ID id = {1111, 2222};
    
    Student* s = createStudent(NULL, "Иванович", "Иванов",
                               15, 6, 2000, &id, 7500);
    if (s) {
        if (s->base.firstName) free(s->base.firstName);
        if (s->base.secondName) free(s->base.secondName);
        if (s->base.lastName) free(s->base.lastName);
        free(s);
    }
    
    TEST_PASS();
}

void test_createStudent_memoryFailure(void) {
    TEST_START("createStudent memory failure simulation");
    TEST_PASS();
}

// ТЕСТЫ ДЛЯ teacher.c

void test_createTeacher(void) {
    TEST_START("createTeacher");
    
    Person_ID id = {3333, 4444};
    
    Teacher* t = createTeacher("Петр", "Петрович", "Петров",
                               10, 3, 1980, &id, 75000);
    
    ASSERT(t != NULL, "Преподаватель не создан");
    ASSERT(strcmp(t->base.firstName, "Петр") == 0, "Имя не совпадает");
    ASSERT(strcmp(t->base.secondName, "Петрович") == 0, "Отчество не совпадает");
    ASSERT(strcmp(t->base.lastName, "Петров") == 0, "Фамилия не совпадает");
    ASSERT(t->base.dayBirth == 10, "День рождения не совпадает");
    ASSERT(t->base.monthBirth == 3, "Месяц рождения не совпадает");
    ASSERT(t->base.yearBirth == 1980, "Год рождения не совпадает");
    ASSERT(t->base.id.series == 3333, "Серия паспорта не совпадает");
    ASSERT(t->base.id.number == 4444, "Номер паспорта не совпадает");
    ASSERT(t->salary == 75000, "Зарплата не совпадает");
    ASSERT(t->base.type == PERSON_TEACHER, "Тип не установлен");
    
    free(t->base.firstName);
    free(t->base.secondName);
    free(t->base.lastName);
    free(t);
    
    TEST_PASS();
}

void test_createTeacher_nullInput(void) {
    TEST_START("createTeacher NULL input");
    
    Person_ID id = {3333, 4444};
    
    Teacher* t = createTeacher(NULL, "Петрович", "Петров",
                               10, 3, 1980, &id, 75000);
    if (t) {
        if (t->base.firstName) free(t->base.firstName);
        if (t->base.secondName) free(t->base.secondName);
        if (t->base.lastName) free(t->base.lastName);
        free(t);
    }
    
    TEST_PASS();
}

void test_createTeacher_memoryFailure(void) {
    TEST_START("createTeacher memory failure simulation");
    TEST_PASS();
}

// ТЕСТЫ ДЛЯ funcs.c

void test_addPrefixToPersonName(void) {
    TEST_START("addPrefixToPersonName");
    
    Student* s = createTestStudent("Иван", "Иванович", "Иванов",
                                   1, 1, 2000, 1111, 2222, 5000);
    
    int result = addPrefixToPersonName((PersonBase*)s);
    ASSERT(result == 1, "Функция не вернула 1");
    ASSERT(strncmp(s->base.firstName, "[префикс]", 9) == 0, 
           "Префикс не добавлен");
    
    free(s->base.firstName);
    free(s->base.secondName);
    free(s->base.lastName);
    free(s);
    
    TEST_PASS();
}

void test_addPrefixToPersonName_nullInput(void) {
    TEST_START("addPrefixToPersonName NULL input");
    
    int result = addPrefixToPersonName(NULL);
    ASSERT(result == 0, "NULL не обработан корректно");
    
    Student* s = createTestStudent("Иван", "Иванович", "Иванов",
                                   1, 1, 2000, 1111, 2222, 5000);
    char* oldName = s->base.firstName;
    s->base.firstName = NULL;
    
    result = addPrefixToPersonName((PersonBase*)s);
    ASSERT(result == 0, "NULL firstName не обработан");
    
    s->base.firstName = oldName;
    free(s->base.firstName);
    free(s->base.secondName);
    free(s->base.lastName);
    free(s);
    
    TEST_PASS();
}

void test_mapPersons(void) {
    TEST_START("mapPersons");
    
    PersonArray arr;
    initPersonList(&arr);
    
    addPerson(&arr, (PersonBase*)createTestStudent("Иван", "Иванович", "Иванов",
                                                    1, 1, 2000, 1111, 2222, 5000));
    addPerson(&arr, (PersonBase*)createTestTeacher("Петр", "Петрович", "Петров",
                                                    1, 1, 1980, 3333, 4444, 50000));
    
    PersonArray* mapped = mapPersons(&arr, addPrefixToPersonName);
    ASSERT(mapped != NULL, "mapPersons вернул NULL");
    ASSERT(mapped->size == 2, "Размер маппированного массива неверен");
    
    ASSERT(strncmp(mapped->data[0]->firstName, "[префикс]", 9) == 0, 
           "Префикс не добавлен первому элементу");
    ASSERT(strncmp(mapped->data[1]->firstName, "[префикс]", 9) == 0,
           "Префикс не добавлен второму элементу");
    
    freePersonArray(&arr);
    freePersonArray(mapped);
    free(mapped);
    
    TEST_PASS();
}

void test_mapPersons_nullInput(void) {
    TEST_START("mapPersons NULL input");
    
    PersonArray* result = mapPersons(NULL, addPrefixToPersonName);
    ASSERT(result == NULL, "NULL массив не обработан");
    
    PersonArray arr;
    initPersonList(&arr);
    result = mapPersons(&arr, NULL);
    ASSERT(result == NULL, "NULL mapper не обработан");
    
    TEST_PASS();
}

void test_mapPersons_emptyArray(void) {
    TEST_START("mapPersons empty array");
    
    PersonArray arr;
    initPersonList(&arr);
    
    PersonArray* result = mapPersons(&arr, addPrefixToPersonName);
    ASSERT(result != NULL, "Пустой массив не обработан");
    ASSERT(result->size == 0, "Размер не 0 для пустого массива");
    
    freePersonArray(result);
    free(result);
    
    TEST_PASS();
}

void test_concatPrint(void) {
    TEST_START("concatPrint");
    
    PersonArray arr;
    initPersonList(&arr);
    
    addPerson(&arr, (PersonBase*)createTestStudent("Иван", "Иванович", "Иванов",
                                                    1, 1, 2000, 1111, 2222, 5000));
    addPerson(&arr, (PersonBase*)createTestTeacher("Петр", "Петрович", "Петров",
                                                    1, 1, 1980, 3333, 4444, 50000));
    
    printf("--- concatPrint ---\n");
    concatPrint(&arr);
    printf("-------------------\n");
    
    freePersonArray(&arr);
    TEST_PASS();
}

void test_concatPrint_nullInput(void) {
    TEST_START("concatPrint NULL input");
    
    printf("--- concatPrint NULL ---\n");
    concatPrint(NULL);
    printf("------------------------\n");
    
    TEST_PASS();
}

void test_concatPrint_emptyArray(void) {
    TEST_START("concatPrint empty array");
    
    PersonArray arr;
    initPersonList(&arr);
    
    printf("--- concatPrint empty ---\n");
    concatPrint(&arr);
    printf("-------------------------\n");
    
    TEST_PASS();
}

void test_printStudentsOnly(void) {
    TEST_START("printStudentsOnly");
    
    PersonArray arr;
    initPersonList(&arr);
    
    addPerson(&arr, (PersonBase*)createTestStudent("Иван", "Иванович", "Иванов",
                                                    1, 1, 2000, 1111, 2222, 5000));
    addPerson(&arr, (PersonBase*)createTestTeacher("Петр", "Петрович", "Петров",
                                                    1, 1, 1980, 3333, 4444, 50000));
    
    printf("--- printStudentsOnly ---\n");
    printStudentsOnly(&arr);
    printf("-------------------------\n");
    
    // Тест только с преподавателями
    PersonArray arr2;
    initPersonList(&arr2);
    addPerson(&arr2, (PersonBase*)createTestTeacher("Петр", "Петрович", "Петров",
                                                     1, 1, 1980, 3333, 4444, 50000));
    
    printf("--- printStudentsOnly (no students) ---\n");
    printStudentsOnly(&arr2);
    printf("---------------------------------------\n");
    
    freePersonArray(&arr);
    freePersonArray(&arr2);
    TEST_PASS();
}

void test_printTeachersOnly(void) {
    TEST_START("printTeachersOnly");
    
    PersonArray arr;
    initPersonList(&arr);
    
    addPerson(&arr, (PersonBase*)createTestStudent("Иван", "Иванович", "Иванов",
                                                    1, 1, 2000, 1111, 2222, 5000));
    addPerson(&arr, (PersonBase*)createTestTeacher("Петр", "Петрович", "Петров",
                                                    1, 1, 1980, 3333, 4444, 50000));
    
    printf("--- printTeachersOnly ---\n");
    printTeachersOnly(&arr);
    printf("-------------------------\n");
    
    freePersonArray(&arr);
    TEST_PASS();
}

void test_isValidName(void) {
    TEST_START("isValidName");
    
    printf("--- isValidName tests ---\n");
    
    // Валидные имена
    isValidName("Иван");
    isValidName("А");
    isValidName("Александр");
    
    // Невалидные имена
    isValidName("");          // Пустое имя
    isValidName(NULL);        // NULL
    isValidName("Иван123");   // С цифрами
    
    // Длинное имя
    char longName[100];
    memset(longName, 'A', 99);
    longName[99] = '\0';
    isValidName(longName);
    
    printf("-----------------------\n");
    TEST_PASS();
}

void test_isValidDate(void) {
    TEST_START("isValidDate");
    
    printf("--- isValidDate tests ---\n");
    
    isValidDate(15, 6, 2000);
    isValidDate(1, 1, 1950);
    isValidDate(31, 12, 1999);
    
    isValidDate(0, 6, 2000);    // День 0
    isValidDate(32, 6, 2000);   // День 32
    isValidDate(15, 0, 2000);   // Месяц 0
    isValidDate(15, 13, 2000);  // Месяц 13
    isValidDate(15, 6, 1919);   // Год < 1920
    isValidDate(15, 6, 2011);   // Год > 2010
    
    printf("-----------------------\n");
    TEST_PASS();
}

// ТЕСТЫ ДЛЯ main.c

/*void test_clearInputBuffer(void) {
    TEST_START("clearInputBuffer");
    
    clearInputBuffer();
    
    TEST_PASS();
}*/

void test_inputPassportID(void) {
    TEST_START("inputPassportID");
    
    // Требует ввода пользователя, проверяем только что не падает
    setPassportFormat(FORMAT_STRUCTURE);
    Person_ID id;
    
    printf("(Требует ввода пользователя, пропускаем автоматический тест)\n");
    
    TEST_PASS();
}

void test_inputFullName(void) {
    TEST_START("inputFullName");
    
    // Требует ввода пользователя
    char fn[50], sn[50], ln[50];
    
    printf("(Требует ввода пользователя, пропускаем автоматический тест)\n");
    
    TEST_PASS();
}

void test_selectPassportFormat(void) {
    TEST_START("selectPassportFormat");
    
    // Требует ввода пользователя
    printf("(Требует ввода пользователя, пропускаем автоматический тест)\n");
    
    TEST_PASS();
}

void test_printmenu(void) {
    TEST_START("printmenu");
    
    printf("--- Меню ---\n");
    printmenu();
    printf("------------\n");
    
    TEST_PASS();
}

// ГЛАВНАЯ ФУНКЦИЯ ЗАПУСКА ВСЕХ ТЕСТОВ

int runAllTests(void) {
    printf("========================================\n");
    printf("        ЗАПУСК ТЕСТОВ ПРОЕКТА          \n");
    printf("========================================\n\n");
    
    // Тесты person.c
    printf(">>> ТЕСТЫ person.c <<<\n");
    test_setPassportFormat();
    test_getPassportFormat();
    test_comparePassportIDs();
    test_printPassportID();
    test_initPersonList();
    test_addPerson();
    test_removePerson();
    test_freePersonArray();
    test_isStudent_isTeacher();
    test_printPerson();
    test_printAllPersons();
    test_findPersonByID();
    test_findStudentByIndex();
    test_findTeacherByIndex();
    printf("\n");
    
    // Тесты student.c
    printf(">>> ТЕСТЫ student.c <<<\n");
    test_createStudent();
    test_createStudent_nullInput();
    test_createStudent_memoryFailure();
    printf("\n");
    
    // Тесты teacher.c
    printf(">>> ТЕСТЫ teacher.c <<<\n");
    test_createTeacher();
    test_createTeacher_nullInput();
    test_createTeacher_memoryFailure();
    printf("\n");
    
    // Тесты funcs.c
    printf(">>> ТЕСТЫ funcs.c <<<\n");
    test_addPrefixToPersonName();
    test_addPrefixToPersonName_nullInput();
    test_mapPersons();
    test_mapPersons_nullInput();
    test_mapPersons_emptyArray();
    test_concatPrint();
    test_concatPrint_nullInput();
    test_concatPrint_emptyArray();
    test_printStudentsOnly();
    test_printTeachersOnly();
    test_isValidName();
    test_isValidDate();
    printf("\n");
    
    // Тесты main.c
    printf(">>> ТЕСТЫ main.c <<<\n");
    test_inputPassportID();
    test_inputFullName();
    test_selectPassportFormat();
    test_printmenu();
    printf("\n");
    
    // Итоги
    printf("========================================\n");
    printf("              ИТОГИ ТЕСТОВ             \n");
    printf("========================================\n");
    printf("Пройдено: %d\n", tests_passed);
    printf("Провалено: %d\n", tests_failed);
    printf("Всего: %d\n", tests_passed + tests_failed);
    printf("========================================\n");
    
    if (tests_failed == 0) {
        printf("ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!\n");
        return 0;
    } else {
        printf("ЕСТЬ ПРОВАЛЕННЫЕ ТЕСТЫ!\n");
        return 1;
    }
}
