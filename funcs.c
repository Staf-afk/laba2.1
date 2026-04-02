#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcs.h"
#include "student.h"
#include "teacher.h"

/*5. Файл funcs.c
Описание:
Содержит вспомогательные функции высшего порядка, функции сложного вывода списков и утилиты валидации ввода.
Функции
int addPrefixToPersonName(PersonBase* p)
Описание:
Добавляет текстовый префикс "[префикс] " к имени человека.
Параметры:
p: Указатель на объект человека.
Возвращаемое значение:
1: Успешно.
0: Ошибка (NULL указатель или неудача malloc).
Побочные эффекты:
Освобождает старую память p->firstName.
Выделяет новую память большей длины.
Изменяет содержимое структуры напрямую.
PersonArray* mapPersons(PersonArray* arr, int (*mapper)(PersonBase*))
Описание:
Реализует паттерн "Map". Создает новый массив людей, копируя всех людей из исходного массива, и применяет функцию-преобразователь (mapper) к каждой копии.
Параметры:
arr: Исходный массив людей.
mapper: Функция-коллбэк, принимающая PersonBase* и возвращающая int (статус).
Возвращаемое значение:
Указатель на новый массив PersonArray.
NULL при ошибке.
Логика:
Создает новый пустой массив.
Для каждого элемента исходного массива определяет тип (Студент/Преподаватель).
Создает глубокую копию объекта (через createStudent/createTeacher).
Применяет mapper к копии.
Добавляет копию в новый массив.
Важно:
Ответственность за освобождение памяти возвращенного массива лежит на вызывающей стороне (см. main.c, case 8).
void concatPrint(PersonArray* persons)
Описание:
Выводит объединенный список, но разделенный по категориям: сначала все студенты, затем все преподаватели. Нумерует их сквозным порядком.
Параметры:
persons: Указатель на массив людей.
Возвращаемое значение:
Отсутствует.
Формат вывода:
Заголовки "--- Студенты ---", "--- Преподаватели ---", итоговое количество человек.
void printStudentsOnly(PersonArray* arr)
Описание:
Выводит только студентов из массива.
Параметры:
arr: Указатель на массив.
Возвращаемое значение:
Отсутствует.
Примечание:
Выводит общее количество найденных студентов в конце.
void printTeachersOnly(PersonArray* arr)
Описание:
Выводит только преподавателей из массива.
Параметры:
arr: Указатель на массив.
Возвращаемое значение:
Отсутствует.
Примечание:
Выводит общее количество найденных преподавателей в конце.
void isValidName(char* name)
Описание:
Выполняет базовую валидацию строки имени.
Параметры:
name: Проверяемая строка.
Возвращаемое значение:
Отсутствует (выводит сообщения об ошибках в консоль).
Проверки:
Пустая строка или NULL.
Длина больше 50 символов.
Наличие цифр в имени.
Примечание:
Функция только информирует об ошибке, не возвращает статус и не исправляет ввод.
void isValidDate(int day, int month, int year)
Описание:
Заглушка для валидации даты.
Параметры:
day, month, year: Компоненты даты.
Возвращаемое значение:
Отсутствует.
Логика:
Содержит условие if, но тело условия пустое {}. Фактически не выполняет никакой проверки и не выводит сообщений.
Примечание:
В текущем виде функция бесполезна.
Блок рекламы (Комментарий)
Описание:
В конце файла присутствует большой закомментированный блок ASCII-арт, предлагающий место для рекламы за дополнительные баллы. Не влияет на компиляцию.*/

int addPrefixToPersonName(PersonBase* p)
{
    if (!p || !p->firstName) return 0;
    char* newFirst = malloc(strlen(p->firstName) + 19);
    if (!newFirst) return 0;
    sprintf(newFirst, "[префикс] %s", p->firstName);
    free(p->firstName);
    p->firstName = newFirst;
    return 1;
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

PersonArray* mapPersons(PersonArray* arr, int (*mapper)(PersonBase*))
{
    if (!arr || !mapper) return NULL;
    
    PersonArray* result = malloc(sizeof(PersonArray));
    if (!result) return NULL;
    initPersonList(result);
    
    for (int i = 0; i < arr->size; i++)
    {
        PersonBase* original = arr->data[i];
        PersonBase* copy = NULL;
        
        if (isStudent(original))
        {
            Student* s = (Student*)original;
            copy = (PersonBase*)createStudent(
                original->firstName, original->secondName, original->lastName,
                original->dayBirth, original->monthBirth, original->yearBirth,
                &original->id, s->scholarship
            );
        }
        else if (isTeacher(original))
        {
            Teacher* t = (Teacher*)original;
            copy = (PersonBase*)createTeacher(
                original->firstName, original->secondName, original->lastName,
                original->dayBirth, original->monthBirth, original->yearBirth,
                &original->id, t->salary
            );
        }
        
        if (copy){
            mapper(copy);
            addPerson(result, copy);
        }
    }
    
    return result;
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

void concatPrint(PersonArray* persons)
{
    printf("\n=== ОБЪЕДИНЁННЫЙ СПИСОК ===\n");
    if (!persons || persons->size == 0){
        printf("  (список пуст)\n");
        return;
    }
    
    printf("  -- Студенты:\n");
    int studentCount = 0;
    for (int i = 0; i < persons->size; i++)
    {
        if (isStudent(persons->data[i]))
        {
            printf("%d", studentCount + 1);
            printPerson(persons->data[i]);
            studentCount++;
        }
    }
    if (studentCount == 0) printf("  (нет студентов)\n");
    
    printf("  -- Преподаватели:\n");
    int teacherCount = 0;
    for (int i = 0; i < persons->size; i++)
    {
        if (isTeacher(persons->data[i])){
            printf("%d", studentCount + teacherCount + 1);
            printPerson(persons->data[i]);
            teacherCount++;
        }
    }
    if (teacherCount == 0) printf("  (нет преподавателей)\n");
    
    printf("  Итого: %d человек\n", persons->size);
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

void printStudentsOnly(PersonArray* arr)
{
    printf("\n=== СТУДЕНТЫ ===\n");
    int count = 0;
    if (!arr || arr->size == 0){
        printf("  (список пуст)\n");
        return;
    }
    for (int i = 0; i < arr->size; i++)
    {
        if (isStudent(arr->data[i]))
        {
            printPerson(arr->data[i]);
            count++;
        }
    }
    if (count == 0) printf("  (нет студентов)\n");
    else printf("  Всего студентов: %d\n", count);
}

void printTeachersOnly(PersonArray* arr)
{
    printf("\n=== ПРЕПОДАВАТЕЛИ ===\n");
    int count = 0;
    if (!arr || arr->size == 0)
    {
        printf("  (список пуст)\n");
        return;
    }
    for (int i = 0; i < arr->size; i++)
    {
        if (isTeacher(arr->data[i]))
        {
            printPerson(arr->data[i]);
            count++;
        }
    }
    if (count == 0)
    {
        printf("  (нет преподавателей)\n");
    }
    else
    { 
        printf("  Всего преподавателей: %d\n", count);
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

void isValidName(char* name)
{
    if (name == NULL || strlen(name) == 0)
    {
        printf("Вы ничего не ввели.\n");
        return;
    }

    if (strlen(name) > 50)
    {
        printf("Сомнительная длина имени.\n");
        return;
    }

    for (int i = 0; name[i] != '\0'; i++){
        if (isdigit((unsigned char)name[i]))
        {
            printf("Вы ввели цифру в имени(что-то явно не так).\n");
            return;  
        }
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

void isValidDate(int day, int month, int year)
{
    if(day >= 32 || day <= 0 || month <= 0 || month >= 13 || year >= 2010 || year <= 1920){}
}




void printPersonPayment(PersonBase* p) {
    if (!p || !p->getPayment) {
        printf("  Нет данных о выплате\n");
        return;
    }
    
    int payment = p->getPayment(p);
    
    if (isStudent(p)) {
        printf("  Стипендия: %d руб.\n", payment);
    } else if (isTeacher(p)) {
        printf("  Зарплата: %d руб.\n", payment);
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