#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tests.h"
#include "teacher.h"
#include "student.h"
#include "funcs.h"
#include "passport.h"

StudentArray students;
TeacherArray teachers;

// Добавлена функция очистки буфера ввода
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Добавлена функция выбора формата паспорта
void selectPassportFormat(void) {
    int choice;
    printf("Выберите формат паспорта:\n");
    printf("[1] - Серия и номер (раздельно)\n");
    printf("[2] - Только серия (упрощенный)\n");
    printf("[3] - Серия и номер (через пробел)\n");
    printf("Выбор: ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    if (choice == 1) {
        setPassportFormat(FORMAT_STRUCTURE);
    } else if (choice == 2) {
        setPassportFormat(FORMAT_SINGLE_NUMBER);
    } else {
        setPassportFormat(FORMAT_SPACE_SEPARATED);
    }
}

void printmenu(void) {
    printf(
        "========МЕНЮ=======\n"
        "[1] - Добавить преподавателя.\n"
        "[2] - Добавить студента.\n"
        "[3] - Удалить преподавателя.\n"
        "[4] - Удалить студента.\n"
        "[5] - Найти человека по ID.\n"
        "[6] - Вывести список студентов.\n"
        "[7] - Вывести список преподавателей.\n"
        "[8] - Вывести всех.\n"
        "[9] - Добавить префикс к именам.\n"
        "[10] - Запустить тесты.\n"
        "[0] - Завершить программу.\n"
        "Выбор: "
    );
}

void inputPassportID(Person_ID* id) {
    if (g_passportFormat == FORMAT_SINGLE_NUMBER) {
        printf("Введите уникальный ID паспорта: ");
        scanf("%d", &id->series);
        id->number = 0;
        clearInputBuffer();
    } else if (g_passportFormat == FORMAT_SPACE_SEPARATED) {
        printf("Введите серию и номер через пробел: ");
        scanf("%d %d", &id->series, &id->number);
        clearInputBuffer();
    } else {
        printf("Введите серию паспорта: ");
        scanf("%d", &id->series);
        clearInputBuffer();
        printf("Введите номер паспорта: ");
        scanf("%d", &id->number);
        clearInputBuffer();
    }
}

void inputFullName(char* firstName, char* secondName, char* lastName) {
    printf("Введите имя: ");
    scanf("%49s", firstName);
    clearInputBuffer();
    printf("Введите отчество: ");
    scanf("%49s", secondName);
    clearInputBuffer();
    printf("Введите фамилию: ");
    scanf("%49s", lastName);
    clearInputBuffer();
}

int main(void) {
    int choice = 1;
    char firstName[50], secondName[50], lastName[50];
    int dayStudentBirth = 0, monthStudentBirth = 0, yearStudentBirth = 0;
    int dayTeacherBirth = 0, monthTeacherBirth = 0, yearTeacherBirth = 0;
    int salary, scholarship;
    int index;
    Person_ID id;
    
    selectPassportFormat();
    initStudentList(&students);
    initTeacherList(&teachers);
    
    while (choice != 0) {
        printmenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice) {
            case 1: {
                printf("\n--- Добавление преподавателя ---\n");
                inputPassportID(&id);
                inputFullName(firstName, secondName, lastName);
                printf("Введите дату рождения (день месяц год): ");
                scanf("%d %d %d", &dayTeacherBirth, &monthTeacherBirth, &yearTeacherBirth);
                clearInputBuffer();
                printf("Введите зарплату: ");
                scanf("%d", &salary);
                clearInputBuffer();
                addTeacher(&teachers, firstName, secondName, lastName,
                          dayTeacherBirth, monthTeacherBirth, yearTeacherBirth,
                          (Teacher_ID*)&id, salary);
                printf("Преподаватель добавлен.\n");
                break;
            }
            case 2: {
                printf("\n--- Добавление студента ---\n");
                inputPassportID(&id);
                inputFullName(firstName, secondName, lastName);
                printf("Введите дату рождения (день месяц год): ");
                scanf("%d %d %d", &dayStudentBirth, &monthStudentBirth, &yearStudentBirth);
                clearInputBuffer();
                printf("Введите стипендию: ");
                scanf("%d", &scholarship);
                clearInputBuffer();
                addStudent(&students, firstName, secondName, lastName,
                          dayStudentBirth, monthStudentBirth, yearStudentBirth,
                          (Student_ID*)&id, scholarship);
                printf("Студент добавлен.\n");
                break;
            }
            case 3: {
                printf("\nВведите индекс преподавателя для удаления: ");
                scanf("%d", &index);
                clearInputBuffer();
                removeTeacher(&teachers, index - 1);
                printf("\n");
                break;
            }
            case 4: {
                printf("\nВведите индекс студента для удаления: ");
                scanf("%d", &index);
                clearInputBuffer();
                removeStudent(&students, index - 1);
                printf("\n");
                break;
            }
            case 5: {
                printf("\n--- Поиск по паспортным данным ---\n");
                inputPassportID(&id);
                findPersonByID(&students, &teachers, id.series, id.number);
                printf("\n");
                break;
            }
            case 6:
                printf("\n");
                printAllStudents(&students);
                printf("\n");
                break;
            case 7:
                printf("\n");
                printAllTeachers(&teachers);
                printf("\n");
                break;
            case 8:
                printf("\n");
                concatPrint(&students, &teachers);
                printf("\n");
                break;
            case 9: {
                StudentArray* mappedStudents = mapStudents(&students, addPrefixToStudentName);
                TeacherArray* mappedTeachers = mapTeachers(&teachers, addPrefixToTeacherName);
                printf("\nПрефикс добавлен к именам.\n");
                concatPrint(mappedStudents, mappedTeachers);
                freeStudentArray(mappedStudents);
                freeTeacherArray(mappedTeachers);
                free(mappedStudents);
                free(mappedTeachers);
                printf("\n");
                break;
            }
            case 10:
                runAllTests();
                printf("\nТесты запущены.\n");
                break;
            case 0:
                printf("Завершение работы.\n");
                freeStudentArray(&students);
                freeTeacherArray(&teachers);
                break;
            default:
                printf("Неверный выбор.\n");
                break;
        }
    }
    return 0;
}