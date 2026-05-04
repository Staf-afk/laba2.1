#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "funcs.h"
//#include "tests.h"

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

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void selectPassportFormat()
{
    int choice;
    int check;

    while (1)
    {
        printf("Выберите формат паспорта:\n");
        printf("[1] - Серия и номер (раздельно)\n");
        printf("[2] - Только серия (упрощенный)\n");
        printf("[3] - Серия и номер (через пробел)\n");
        printf("Выбор: ");

        check = scanf("%d", &choice);
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
    
    printf("Введите имя: ");
    scanf("%49s", firstName);
    err = isValidName(firstName);

    if(err != ERROR_OK)
    {
        printf("Ошибка: %s\n", errorInWords(err));
    }
    clearInputBuffer();
    
    printf("Введите отчество: ");
    scanf("%49s", secondName);
    err = isValidName(secondName);

    if(err != ERROR_OK)
    {
        printf("Ошибка: %s\n", errorInWords(err));
    }
    clearInputBuffer();
    
    printf("Введите фамилию: ");
    scanf("%49s", lastName);
    err = isValidName(lastName);

    if(err != ERROR_OK)
    {
        printf("Ошибка: %s\n", errorInWords(err));
    }
    clearInputBuffer();
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

int main(void)
{   
    /*
    printf("Для запуска программы пройдите тест на адекватность.\n");
    int captcha0, captcha1, captcha2, captcha3, captcha4, captcha5, captcha6, captcha7, captcha8, captcha9, captcha10;
    int checkcaptcha0, checkcaptcha1, checkcaptcha2, checkcaptcha3, checkcaptcha4, checkcaptcha5, checkcaptcha6, checkcaptcha7, checkcaptcha8, checkcaptcha9, checkcaptcha10;
    int testcaptcha; 
    while(testcaptcha != 1){
        printf("Первый тест - типо каптча.\n");
        printf("Введите число 0. \nВвод: ");
        checkcaptcha0 = scanf("%d", &captcha0);
        clearInputBuffer();
        printf("Введите число 1. \nВвод: ");
        checkcaptcha1 = scanf("%d", &captcha1);
        clearInputBuffer();
        printf("Введите число 2. \nВвод: ");
        checkcaptcha2 = scanf("%d", &captcha2);
        clearInputBuffer();
        printf("Введите число 3. \nВвод: ");
        checkcaptcha3 = scanf("%d", &captcha3);
        clearInputBuffer();
        printf("Введите число 4. \nВвод: ");
        checkcaptcha4 = scanf("%d", &captcha4);
        clearInputBuffer();
        printf("Введите число 5. \nВвод: ");
        checkcaptcha5 = scanf("%d", &captcha5);
        clearInputBuffer();
        printf("Введите число 6. \nВвод: ");
        checkcaptcha6 = scanf("%d", &captcha6);
        clearInputBuffer();
        printf("Введите число 7. \nВвод: ");
        checkcaptcha7 = scanf("%d", &captcha7);
        clearInputBuffer();
        printf("Введите число 8. \nВвод: ");
        checkcaptcha8 = scanf("%d", &captcha8);
        clearInputBuffer();
        printf("Введите число 9. \nВвод: ");
        checkcaptcha9 = scanf("%d", &captcha9);
        clearInputBuffer();
        printf("Введите число 10. \nВвод: ");
        checkcaptcha10 = scanf("%d", &captcha10);
        clearInputBuffer();

        if(captcha0 == 0 && captcha1 == 1 && captcha2 == 2 && captcha3 == 3 && captcha4 == 4 && captcha5 == 5 && captcha6 == 6 && captcha7 == 7 
            && captcha8 == 8 && captcha9 == 9 && captcha10 == 10 && checkcaptcha0 == 1 && checkcaptcha1 == 1 && 
            checkcaptcha2 == 1 && checkcaptcha3 == 1 && checkcaptcha4 == 1 && checkcaptcha5 == 1 && checkcaptcha6 == 1 &&
            checkcaptcha7 == 1 && checkcaptcha8 == 1 && checkcaptcha9 == 1 && checkcaptcha10 == 1)
        {
            testcaptcha = 1;
            printf("Первый этап проверки пройден.\n");
        }
        else
        {
            printf("Каптча не пройдена, попробуйте еще раз.\n");
            testcaptcha = 0;
        }
    }
    int testAns = 0;
    int ans, lastCheck;
    while(testAns != 1){
        
        printf("Сейчас будет пользовательсое соглашение.\n");
        printf(
            "1. ВЫ ПРИНИМАЕТЕ ЭТО СОГЛАШЕНИЕ, КОГДА СМОТРИТЕ НА ЭКРАН ДОЛЬШЕ 3 СЕКУНД.\n"
            "- Если вы не согласны - закройте глаза и отвернитесь.\n\n"
            "2. АВТОР НЕ ГАРАНТИРУЕТ:\n"
                "- Что программа скомпилируется(с первого раза) (она скомпилируется, но будет обижена на твой компилятор);\n"
            " - Что 'free()' освободит что-то кроме вашего времени.\n\n"
            "3. ПОЛЬЗОВАТЕЛЬ ОБЯЗУЕТСЯ:\n"
                "- Признать, что 'int main()' без void ? это стиль хакера 80-х.\n"
                "- Не использовать программу для управления ядерными реакторами, тостерами и бывшими;\n"
                "- Скопировать этот файл на флешку и подарить врагу (передача лицензии добровольна, но обязательна).\n\n"
                "4. ОСОБЫЕ УСЛОВИЯ:\n"
                "- Если программа напечатает \"Hello, World!\", значит, она поздоровалась лично с тобой.\n"
                "Ты должен ответить \"Hello, Code!\" вслух. Иначе соглашение аннулируется.\n"
                "- Все баги(по умолчанию) являются фичами. Баг, который не исчезает после перезагрузки ? это карма.\n\n"
                "ПО ПОВОДУ РЕКЛАМЫ В КОДЕ:\n"
                "- Для добавления вашей рекламы - выйграйте автора в 'крестики нолики'"
                "Для подтверждения того, что вы ознакомлены с соглашением введите количество нулей у 217! (217 факториал)\n Ввод:"
        );
        lastCheck = scanf("%d", &ans);
        clearInputBuffer();
        if(ans == 52 && lastCheck == 1)
        {
            testAns = 1;
            printf("Вы прошли эту нелегкую проверку и вам открывается доступ к программе. Пожалуйста, не ломайте ее полностью.\n\n\n");
        }
        else{
            printf("Попробуйте еще раз прочитать и все осмыслить.\n");
        }
    }

    */


    int choice = 1;
    int check1 = 0;
    char firstName[50], secondName[50], lastName[50];
    uint8_t dayBirth = 0, monthBirth = 0, yearBirth = 0;
    int salary, scholarship;
    int index;
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
                
                printf("Введите дату рождения (день месяц год): ");
                scanf("%d %d %d", &dayBirth, &monthBirth, &yearBirth);
                clearInputBuffer();
                
                err = isValidDate(dayBirth, monthBirth, yearBirth);
                if(err != ERROR_OK){
                    printf("Ошибка: %s\n", errorInWords(err));
                    break;
                }
                
                printf("Введите зарплату: ");
                scanf("%d", &salary);
                clearInputBuffer();
                
                Teacher* t = createTeacher(firstName, secondName, lastName,
                                          dayBirth, monthBirth, yearBirth,
                                          &id, salary);
                if (t){
                    err = addPerson(&people, (PersonBase*)t);
                    if(err == ERROR_OK){
                        printf("Преподаватель добавлен.\n");
                    } 
                    else{
                        printf("Ошибка добавления: %s\n", errorInWords(err));
                        // Освобождаем память, если добавить не удалось
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
                
                printf("Введите дату рождения (день месяц год): ");
                scanf("%d %d %d", &dayBirth, &monthBirth, &yearBirth);
                clearInputBuffer();
                
                err = isValidDate(dayBirth, monthBirth, yearBirth);
                if(err != ERROR_OK){
                    printf("Ошибка: %s\n", errorInWords(err));
                    break;
                }
                
                printf("Введите стипендию: ");
                scanf("%d", &scholarship);
                clearInputBuffer();
                
                Student* s = createStudent(firstName, secondName, lastName,
                                          dayBirth, monthBirth, yearBirth,
                                          &id, scholarship);
                if (s){
                    err = addPerson(&people, (PersonBase*)s);
                    if(err == ERROR_OK){
                        printf("Студент добавлен.\n");
                    } 
                    else {
                        printf("Ошибка добавления: %s\n", errorInWords(err));
                        free(s->base.firstName);
                        free(s->base.secondName);
                        free(s->base.lastName);
                        free(s);
                    }
                } 
                else {
                    printf("Ошибка создания студента\n");
                }
                break;
            }
            case 3: {
                printf("\nВведите индекс человека для удаления: ");
                scanf("%d", &index);
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
                for (int i = 0; i < people.size; i++) {
                    printPerson(people.data[i]);
                    printPersonPayment(people.data[i]);
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