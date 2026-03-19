#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "funcs.h"

PersonArray people;

void clearInputBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void selectPassportFormat(void){
    int choice;
    printf("Выберите формат паспорта:\n");
    printf("[1] - Серия и номер (раздельно)\n");
    printf("[2] - Только серия (упрощенный)\n");
    printf("[3] - Серия и номер (через пробел)\n");
    printf("Выбор: ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    if (choice == 1){
        setPassportFormat(FORMAT_STRUCTURE);
    }
    else if (choice == 2){
        setPassportFormat(FORMAT_SINGLE_NUMBER);
    }
    else{
        setPassportFormat(FORMAT_SPACE_SEPARATED);
    }
}

void printmenu(void){
    printf(
        "========МЕНЮ=======\n"
        "[1] - Добавить преподавателя.\n"
        "[2] - Добавить студента.\n"
        "[3] - Удалить человека.\n"
        "[4] - Найти человека по ID.\n"
        "[5] - Вывести список студентов.\n"
        "[6] - Вывести список преподавателей.\n"
        "[7] - Вывести всех.\n"
        "[8] - Добавить префикс к именам.\n"
        "[9] - Запустить тесты.\n"
        "[0] - Завершить программу.\n"
        "Выбор: "
    );
}

void inputPassportID(Person_ID* id){
    if (g_passportFormat == FORMAT_SINGLE_NUMBER){
        printf("Введите уникальный ID паспорта: ");
        scanf("%d", &id->series);
        id->number = 0;
        clearInputBuffer();
    }
    else if (g_passportFormat == FORMAT_SPACE_SEPARATED){
        printf("Введите серию и номер через пробел: ");
        scanf("%d %d", &id->series, &id->number);
        clearInputBuffer();
    }
    else{
        printf("Введите серию паспорта: ");
        scanf("%d", &id->series);
        clearInputBuffer();
        printf("Введите номер паспорта: ");
        scanf("%d", &id->number);
        clearInputBuffer();
    }
}

void inputFullName(char* firstName, char* secondName, char* lastName){
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

int main(void){
    int choice = 1;
    char firstName[50], secondName[50], lastName[50];
    int dayBirth = 0, monthBirth = 0, yearBirth = 0;
    int salary, scholarship;
    int index;
    Person_ID id;
    
    selectPassportFormat();
    initPersonList(&people);
    
    while (choice != 0){
        printmenu();
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch (choice){
            case 1: {
                printf("\n--- Добавление преподавателя ---\n");
                inputPassportID(&id);
                inputFullName(firstName, secondName, lastName);
                printf("Введите дату рождения (день месяц год): ");
                scanf("%d %d %d", &dayBirth, &monthBirth, &yearBirth);
                clearInputBuffer();
                printf("Введите зарплату: ");
                scanf("%d", &salary);
                clearInputBuffer();
                
                Teacher* t = createTeacher(firstName, secondName, lastName,
                                          dayBirth, monthBirth, yearBirth,
                                          &id, salary);
                if (t){
                    addPerson(&people, (PersonBase*)t);
                    printf("Преподаватель добавлен.\n");
                }
                break;
            }
            case 2: {
                printf("\n--- Добавление студента ---\n");
                inputPassportID(&id);
                inputFullName(firstName, secondName, lastName);
                printf("Введите дату рождения (день месяц год): ");
                scanf("%d %d %d", &dayBirth, &monthBirth, &yearBirth);
                clearInputBuffer();
                printf("Введите стипендию: ");
                scanf("%d", &scholarship);
                clearInputBuffer();
                
                Student* s = createStudent(firstName, secondName, lastName,
                                          dayBirth, monthBirth, yearBirth,
                                          &id, scholarship);
                if (s){
                    addPerson(&people, (PersonBase*)s);
                    printf("Студент добавлен.\n");
                }
                break;
            }
            case 3: {
                printf("\nВведите индекс человека для удаления: ");
                scanf("%d", &index);
                clearInputBuffer();
                removePerson(&people, index - 1);
                printf("\n");
                break;
            }
            case 4: {
                printf("\n--- Поиск по паспортным данным ---\n");
                inputPassportID(&id);
                PersonBase* p = findPersonByID(&people, id.series, id.number);
                if (p){
                    printf("Найден:\n");
                    printPerson(p);
                }
                else{
                    printf("Человек с таким паспортом не найден.\n");
                }
                printf("\n");
                break;
            }
            case 5:{
                printf("\n");
                printStudentsOnly(&people);
                printf("\n");
                break;
            }
            case 6:{
                printf("\n");
                printTeachersOnly(&people);
                printf("\n");
                break;
            }
            case 7:{
                printf("\n");
                concatPrint(&people);
                printf("\n");
                break;
            }
            case 8: {
                PersonArray* mapped = mapPersons(&people, addPrefixToPersonName);
                printf("\nПрефикс добавлен к именам.\n");
                concatPrint(mapped);
                freePersonArray(mapped);
                free(mapped);
                printf("\n");
                break;
            }
            case 9:{
                printf("\nТесты запущены.\n");
                break;
            }
            case 0:{
                printf("Завершение работы.\n");
                freePersonArray(&people);
                break;
            }
            default:{
                printf("Неверный выбор.\n");
                break;
            }
        }
    }
    return 0;
}