#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "funcs.h"
#include "tests.h"

/*Описание:
Основной файл программы, содержащий точку входа (main) и логику пользовательского интерфейса (CLI). Отвечает за отображение меню, обработку ввода пользователя, координацию создания объектов и управление жизненным циклом программы.
Функции
void clearInputBuffer(void)
Описание:
Очищает буфер стандартного ввода (stdin) от остаточных символов (обычно символа новой строки \n), оставшихся после предыдущего ввода (например, после scanf). Это предотвращает пропуск последующих вызовов ввода строк.
Параметры:
Отсутствуют.
Возвращаемое значение:
Отсутствует.
Примечание:
Использует цикл while, читающий символы до тех пор, пока не встретится \n или EOF.
void selectPassportFormat(void)
Описание:
Предоставляет пользователю меню для выбора формата хранения и ввода паспортных данных. Устанавливает глобальную переменную формата паспорта.
Параметры:
Отсутствуют.
Возвращаемое значение:
Отсутствует.
Побочные эффекты:
Выводит меню в консоль.
Считывает выбор пользователя.
Вызывает setPassportFormat для установки глобального состояния.
Варианты формата:
FORMAT_STRUCTURE: Серия и номер вводятся раздельно.
FORMAT_SINGLE_NUMBER: Только серия (упрощенный ID).
FORMAT_SPACE_SEPARATED: Серия и номер через пробел в одну строку.
void printmenu(void)
Описание:
Выводит главное меню программы на экран. Содержит список доступных действий (добавление, удаление, поиск, вывод списков, тесты, выход).
Параметры:
Отсутствуют.
Возвращаемое значение:
Отсутствует.
void inputPassportID(Person_ID* id)
Описание:
Запрашивает у пользователя ввод паспортных данных в зависимости от текущего выбранного формата (g_passportFormat). Заполняет структуру Person_ID.
Параметры:
id: Указатель на структуру Person_ID, которую необходимо заполнить.
Возвращаемое значение:
Отсутствует.
Логика:
Если формат SINGLE_NUMBER: запрашивает только серию, номер устанавливается в 0.
Если формат SPACE_SEPARATED: запрашивает серию и номер через пробел.
Иначе (STRUCTURE): запрашивает серию и номер отдельными запросами.
Примечание:
После каждого scanf вызывается clearInputBuffer.
void inputFullName(char* firstName, char* secondName, char* lastName)
Описание:
Запрашивает у пользователя ввод ФИО (Имя, Отчество, Фамилия).
Параметры:
firstName: Буфер для имени (макс. 49 символов + \0).
secondName: Буфер для отчества.
lastName: Буфер для фамилии.
Возвращаемое значение:
Отсутствует.
Примечание:
Использует scanf("%49s", ...) для ограничения длины ввода. После ввода каждого поля вызывается функция валидации isValidName, однако возврат валидации не проверяется (ввод не перезапрашивается при ошибке).
int main(void)
Описание:
Точка входа в программу. Инициализирует систему, запускает главный цикл обработки меню и освобождает ресурсы перед завершением.
Параметры:
Отсутствуют.
Возвращаемое значение:
0: Успешное завершение.
Логика работы:
Выбор формата паспорта.
Инициализация списка людей (initPersonList).
Цикл while, работающий до выбора пункта "0".
Обработка выбора через switch:
1: Создание преподавателя (createTeacher, addPerson).
2: Создание студента (createStudent, addPerson).
3: Удаление по индексу (removePerson).
4: Поиск по паспортным данным (findPersonByID).
5-7: Вывод списков (студенты, преподаватели, все).
8: Применение префикса к именам через mapPersons.
9: Запуск тестов (runAllTests).
0: Очистка памяти (freePersonArray) и выход.
Локальные переменные:
Буферы для ввода (имена, даты, ID).
Переменная выбора меню choice.*/

PersonArray people;

void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void selectPassportFormat(void)
{
    int choice;
    printf("Выберите формат паспорта:\n");
    printf("[1] - Серия и номер (раздельно)\n");
    printf("[2] - Только серия (упрощенный)\n");
    printf("[3] - Серия и номер (через пробел)\n");
    printf("Выбор: ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    if (choice == 1)
    {
        setPassportFormat(FORMAT_STRUCTURE);
    }
    else if (choice == 2)
    {
        setPassportFormat(FORMAT_SINGLE_NUMBER);
    }
    else
    {
        setPassportFormat(FORMAT_SPACE_SEPARATED);
    }
}

void printmenu(void)
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
        "[9] - Запустить тесты.\n"
        "[10] - Вывести доходы людей.\n "
        "[0] - Завершить программу.\n"
        "Выбор: "
    );
}

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

void inputFullName(char* firstName, char* secondName, char* lastName)
{
    printf("Введите имя: ");
    scanf("%49s", firstName);
    isValidName(firstName);
    clearInputBuffer();
    printf("Введите отчество: ");
    scanf("%49s", secondName);
    isValidName(secondName);
    clearInputBuffer();
    printf("Введите фамилию: ");
    scanf("%49s", lastName);
    isValidName(lastName);
    clearInputBuffer();
}

int main(void)
{
    int choice = 1;
    char firstName[50], secondName[50], lastName[50];
    int dayBirth = 0, monthBirth = 0, yearBirth = 0;
    int salary, scholarship;
    int index;
    Person_ID id;
    
    selectPassportFormat();
    initPersonList(&people);
    
    while (choice != 0)
    {
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
            case 2: 
            {
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
            case 3: 
            {
                printf("\nВведите индекс человека для удаления: ");
                scanf("%d", &index);
                clearInputBuffer();
                if (index < 1 || index > people.size){
                    printf("Неверный индекс (должен быть от 1 до %d)\n", people.size);
                } 
                else{
                    removePerson(&people, index - 1);
                }
                printf("\n");
                break;
            }
            case 4: 
            {
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
            case 5:
            {
                printf("\n");
                printStudentsOnly(&people);
                printf("\n");
                break;
            }
            case 6:
            {
                printf("\n");
                printTeachersOnly(&people);
                printf("\n");
                break;
            }
            case 7:
            {
                printf("\n");
                concatPrint(&people);
                printf("\n");
                break;
            }
            case 8: 
            {
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
            case 9:
            {
                runAllTests();
                printf("\nТесты запущены.\n");
                break;
            }
            case 10:
            {
                printf("\n=== ВЫПЛАТЫ ===\n");
                for (int i = 0; i < people.size; i++) {
                    printPerson(people.data[i]);
                    printPersonPayment(people.data[i]);
                }
                printf("\n");
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