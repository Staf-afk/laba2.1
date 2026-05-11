#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "funcs.h"


PersonArray people;

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

CurrencyType selectCurrency()
{
    uint8_t choice;
    printf("Выберите валюту:\n");
    printf("[1] - Рубли (RUB)\n");
    printf("[2] - Доллары (USD)\n");
    printf("Выбор: ");
    scanf("%" SCNu8, &choice);
    clearInputBuffer();
    
    return (choice == 2) ? CURRENCY_USD : CURRENCY_RUB;
}

void selectPassportFormat()
{
    uint8_t choice;
    uint8_t check;

    while (1)
    {
        printf("Выберите формат паспорта:\n");
        printf("[1] - Серия и номер (раздельно)\n");
        printf("[2] - Только серия (упрощенный)\n");
        printf("[3] - Серия и номер (через пробел)\n");
        printf("Выбор: ");

        check = scanf("%" SCNu8, &choice);
        clearInputBuffer();

        if (check != 1 || choice < 1 || choice > 3)
        {
            printf("Ошибка ввода. Пожалуйста, введите число от 1 до 3.\n");
            continue;
        }

        switch (choice)
        {
            case 1: setPassportFormat(FORMAT_STRUCTURE);       
            break;

            case 2: setPassportFormat(FORMAT_SINGLE_NUMBER);   
            break;

            case 3: setPassportFormat(FORMAT_SPACE_SEPARATED); 
            break;

        }

        break; 
    }
}

void printmenu()
{
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
      //  "[9] - Запустить тесты.\n"
        "[9] - Вывести доходы людей.\n "
        "[0] - Завершить программу.\n"
        "Выбор: "
    );
}


/*================================================
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||   ЗДЕСЬ МОГЛА БЫ БЫТЬ ВАША РЕКЛАМА,           ||
||      ЛИШЬ ЗА  ДОП БАЛЛЫ ЗА ЛАБУ               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
==================================================*/

void inputPassportID(Person_ID* id)
{
    if (g_passportFormat == FORMAT_SINGLE_NUMBER)
    {
        printf("Введите уникальный ID паспорта: ");
        scanf("%d", &id->series);
        id->number = 0;
        clearInputBuffer();
    }
    else if (g_passportFormat == FORMAT_SPACE_SEPARATED)
    {
        printf("Введите серию и номер через пробел: ");
        scanf("%d %d", &id->series, &id->number);
        clearInputBuffer();
    }
    else
    {
        printf("Введите серию паспорта: ");
        scanf("%d", &id->series);
        clearInputBuffer();
        printf("Введите номер паспорта: ");
        scanf("%d", &id->number);
        clearInputBuffer();
    }
}

void inputFullName(char* firstName, char* secondName, char* lastName){
    CodeError err;
    int valid = 0;
    while (valid != 1){
        printf("Введите имя: ");
        scanf("%49s", firstName);
        err = isValidName(firstName);
        clearInputBuffer();
        if(err != ERROR_OK){
            printf("Ошибка: %s\n", errorInWords(err));
            printf("Повторите ввод имени.\n");
            continue;
        }
        valid = 1;
    }
    
    valid = 0;
    while (valid != 1){
        printf("Введите отчество: ");
        scanf("%49s", secondName);
        err = isValidName(secondName);
        clearInputBuffer();
        
        if(err != ERROR_OK){
            printf("Ошибка: %s\n", errorInWords(err));
            printf("Повторите ввод отчества.\n");
            continue;
        }
        valid = 1;
    }
    
    valid = 0;
    while (valid != 1){
        printf("Введите фамилию: ");
        scanf("%49s", lastName);
        err = isValidName(lastName);
        clearInputBuffer();
        if(err != ERROR_OK) {
            printf("Ошибка: %s\n", errorInWords(err));
            printf("Повторите ввод фамилии.\n");
            continue;
        }
        valid = 1;
    }
}

int main(void)
{   
    uint8_t choice = 1;
    uint8_t check1 = 0;
    char firstName[50], secondName[50], lastName[50];
    uint8_t dayBirth = 0, monthBirth = 0;
    uint16_t yearBirth = 0;
    unsigned int salary, scholarship;
    size_t index;
    Person_ID id;
    CodeError err;

    selectPassportFormat();
    err = initPersonList(&people);
    if(err != ERROR_OK){
        printf("Ошибка инициализации: %s\n", errorInWords(err));
        return 1;
    }
    
    while (choice != 0)
    {
        printmenu();
        check1 = scanf("%d", &choice);
        clearInputBuffer();
        
        if (check1 != 1 || choice < 0 || choice > 10)
        {
            printf("Ошибка ввода. Пожалуйста, введите число от 0 до 10.\n");
            continue;
        }

        switch (choice){
            case 1: {
                printf("\n--- Добавление преподавателя ---\n");
                inputPassportID(&id);
                inputFullName(firstName, secondName, lastName);
                printf("Введите дату рождения через пробел (день месяц год): ");
                scanf("%hhu %hhu %hu", &dayBirth, &monthBirth, &yearBirth);
                clearInputBuffer();
                //printf("%u %u %u", dayBirth, monthBirth, yearBirth);
                
                err = isValidDate(dayBirth, monthBirth, yearBirth);
                if(err != ERROR_OK){
                    printf("Ошибка: %s\n", errorInWords(err));
                    break;
                }
                CurrencyType currency = selectCurrency();  
                
                printf("Введите зарплату: ");
                scanf("%u", &salary);
            //    printf("%u", salary);
                clearInputBuffer();
                
                Teacher* t = createTeacher(firstName, secondName, lastName,
                                        dayBirth, monthBirth, yearBirth,
                                        &id, salary, currency);
                if (t){
                    err = addPerson(&people, (PersonBase*)t);
                    if(err == ERROR_OK){
                        printf("Преподаватель добавлен.\n");
                    } 
                    else{
                        printf("Ошибка добавления: %s\n", errorInWords(err));
                        free(t->base.firstName);
                        free(t->base.secondName);
                        free(t->base.lastName);
                        free(t);
                    }
                } 
                else{
                    printf("Ошибка создания преподавателя\n");
                }
                break;
            }
            case 2: {
                printf("\n--- Добавление студента ---\n");
                inputPassportID(&id);
                inputFullName(firstName, secondName, lastName);
                
                printf("Введите дату рождения через пробел (день месяц год): ");
                scanf("%hhu %hhu %hu", &dayBirth, &monthBirth, &yearBirth);
                clearInputBuffer();
                err = isValidDate(dayBirth, monthBirth, yearBirth);
                if(err != ERROR_OK){
                    printf("Ошибка: %s\n", errorInWords(err));
                    break;
                }
                CurrencyType currency = selectCurrency();
                printf("Введите стипендию: ");
                scanf("%u", &scholarship);
                clearInputBuffer();
                Student* s = createStudent(firstName, secondName, lastName,
                                        dayBirth, monthBirth, yearBirth,
                                        &id, scholarship, currency);
                if (s){
                    err = addPerson(&people, (PersonBase*)s);
                    if(err == ERROR_OK){
                        printf("Студент добавлен.\n");
                    } 
                    else{
                        printf("Ошибка добавления: %s\n", errorInWords(err));
                        free(s->base.firstName);
                        free(s->base.secondName);
                        free(s->base.lastName);
                        free(s);
                    }
                } 
                else{
                    printf("Ошибка создания студента\n");
                }
                break;
            }
            case 3: {
                printf("\nВведите индекс человека для удаления: ");
                scanf("%zu", &index);
                clearInputBuffer();
                
                err = removePerson(&people, index - 1);
                if(err == ERROR_OK){
                    printf("Человек удалён.\n");
                } 
                else {
                    printf("Ошибка удаления: %s\n", errorInWords(err));
                }
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
                else {
                    printf("Человек с таким паспортом не найден.\n");
                }
                printf("\n");
                break;
            }
            case 5: {
                printf("\n");
                printStudentsOnly(&people);
                printf("\n");
                break;
            }
            case 6: {
                printf("\n");
                printTeachersOnly(&people);
                printf("\n");
                break;
            }
            case 7: {
                printf("\n");
                concatPrint(&people);
                printf("\n");
                break;
            }
            case 8: {
                PersonArray* mapped = mapPersons(&people, addPrefixToPersonName);
                if (mapped){
                    printf("\nПрефикс добавлен к именам.\n");
                    concatPrint(mapped);
                    freePersonArray(mapped);
                    free(mapped);
                } 
                else{
                    printf("Ошибка при добавлении префикса.\n");
                }
                printf("\n");
                break;
            }
            case 9: {
                printf("\n    Официальный доход лиц     \n");
                for (size_t i = 0; i < people.size; i++) {
                    printPerson(&people.data[i]);
                    printPersonPayment(&people.data[i]);
                }
                printf("\n");
                break;
            }
            case 0: {
                printf("Завершение работы.\n");
                freePersonArray(&people);
                break;
            }
        }
    }
    return 0;
}

/*================================================
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||   ЗДЕСЬ МОГЛА БЫ БЫТЬ ВАША РЕКЛАМА,           ||
||      ЛИШЬ ЗА  ДОП БАЛЛЫ ЗА ЛАБУ               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
==================================================*/