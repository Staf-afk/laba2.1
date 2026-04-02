#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"

/*2. Файл person.c
Описание:
Реализует базовую логику работы со структурой PersonBase и массивом людей PersonArray. Содержит функции управления памятью, поиска, сравнения и полиморфного вывода.
Глобальные переменные
PassportFormat g_passportFormat
Описание:
Глобальная переменная, хранящая текущий режим работы с паспортными данными. Инициализируется значением FORMAT_STRUCTURE.
Функции
void setPassportFormat(PassportFormat format)
Описание:
Устанавливает значение глобальной переменной g_passportFormat.
Параметры:
format: Желаемый формат паспорта.
Возвращаемое значение:
Отсутствует.
PassportFormat getPassportFormat(void)
Описание:
Возвращает текущее значение формата паспорта.
Параметры:
Отсутствуют.
Возвращаемое значение:
Текущее значение PassportFormat.
int comparePassportIDs(Person_ID* id1, Person_ID* id2)
Описание:
Сравнивает два паспортных ID с учетом текущего глобального формата.
Параметры:
id1: Первый идентификатор.
id2: Второй идентификатор.
Возвращаемое значение:
1 (истина): Если идентификаторы совпадают.
0 (ложь): Если не совпадают или один из указателей NULL.
Логика:
В режиме FORMAT_SINGLE_NUMBER сравнивается только поле series.
В остальных режимах сравниваются и series, и number.
void printPassportID(Person_ID* id)
Описание:
Выводит паспортные данные в консоль в соответствии с текущим форматом.
Параметры:
id: Указатель на идентификатор.
Возвращаемое значение:
Отсутствует.
Примечание:
Если id равен NULL, функция завершается немедленно.
void initPersonList(PersonArray* arr)
Описание:
Инициализирует структуру массива людей. Устанавливает указатель на данные в NULL и размер в 0.
Параметры:
arr: Указатель на структуру PersonArray.
Возвращаемое значение:
Отсутствует.
Важно:
Не выделяет память для самого массива данных, только подготавливает структуру.
void addPerson(PersonArray* arr, PersonBase* person)
Описание:
Добавляет указатель на человека в динамический массив. Увеличивает размер массива на 1 с помощью realloc.
Параметры:
arr: Указатель на массив людей.
person: Указатель на добавляемый объект (Студент или Преподаватель).
Возвращаемое значение:
Отсутствует.
Обработка ошибок:
Если realloc возвращает NULL, выводится сообщение об ошибке, память не меняется, функция завершается.
void removePerson(PersonArray* arr, int index)
Описание:
Удаляет человека из массива по индексу. Освобождает память, занятую полями структуры (имена) и самой структурой. Сдвигает оставшиеся элементы массива.
Параметры:
arr: Указатель на массив людей.
index: Индекс удаляемого элемента (0-based).
Возвращаемое значение:
Отсутствует.
Логика:
Проверка границ индекса.
Освобождение памяти полей firstName, secondName, lastName и самого объекта person.
Если массив становится пустым, освобождается массив указателей.
Если массив не пуст, элементы сдвигаются влево, и массив уменьшается через realloc.
Примечание:
В коде присутствует дублирование проверки if (arr->size == 1), что является избыточным, но не критичным.
void freePersonArray(PersonArray* arr)
Описание:
Полностью освобождает память, занятую массивом людей и всеми объектами внутри него.
Параметры:
arr: Указатель на массив людей.
Возвращаемое значение:
Отсутствует.
Примечание:
После вызова массив считается пустым (size = 0, data = NULL).
int isStudent(PersonBase* p)
Описание:
Проверяет, является ли указанный объект студентом.
Параметры:
p: Указатель на базовую структуру человека.
Возвращаемое значение:
1: Если p->type == PERSON_STUDENT.
0: В противном случае.
int isTeacher(PersonBase* p)
Описание:
Проверяет, является ли указанный объект преподавателем.
Параметры:
p: Указатель на базовую структуру человека.
Возвращаемое значение:
1: Если p->type == PERSON_TEACHER.
0: В противном случае.
void printPerson(PersonBase* p)
Описание:
Полиморфная функция вывода информации о человеке. Определяет тип объекта и выводит специфичные поля (стипендия для студента, зарплата для преподавателя).
Параметры:
p: Указатель на объект человека.
Возвращаемое значение:
Отсутствует.
Примечание:
Выполняет приведение типов (Student*) или (Teacher*) для доступа к специфичным полям.
void printAllPersons(PersonArray* arr)
Описание:
Итерирует по массиву и выводит информацию о каждом человеке через printPerson.
Параметры:
arr: Указатель на массив людей.
Возвращаемое значение:
Отсутствует.
PersonBase* findPersonByID(PersonArray* arr, int series, int number)
Описание:
Ищет человека в массиве по паспортным данным.
Параметры:
arr: Указатель на массив людей.
series: Серия паспорта для поиска.
number: Номер паспорта для поиска.
Возвращаемое значение:
Указатель на найденный объект PersonBase, если найден.
NULL, если не найден или массив пуст.
Логика:
Использует comparePassportIDs для сравнения.
Student* findStudentByIndex(PersonArray* arr, int index)
Описание:
Безопасно получает студента по индексу в общем массиве.
Параметры:
arr: Указатель на массив.
index: Индекс элемента.
Возвращаемое значение:
Указатель на Student, если элемент существует и является студентом.
NULL в противном случае.
Teacher* findTeacherByIndex(PersonArray* arr, int index)
Описание:
Безопасно получает преподавателя по индексу в общем массиве.
Параметры:
arr: Указатель на массив.
index: Индекс элемента.
Возвращаемое значение:
Указатель на Teacher, если элемент существует и является преподавателем.
NULL в противном случае.*/

PassportFormat g_passportFormat = FORMAT_STRUCTURE;

void setPassportFormat(PassportFormat format)
{
    g_passportFormat = format;
}

PassportFormat getPassportFormat(void)
{
    return g_passportFormat;
}

int comparePassportIDs(Person_ID* id1, Person_ID* id2)
{
    if(!id1 || !id2) return 0;
    if(g_passportFormat == FORMAT_SINGLE_NUMBER){
        return (id1->series == id2->series);
    }
    else{
        return (id1->series == id2->series && id1->number == id2->number);
    }
}

void printPassportID(Person_ID* id)
{
    if(!id) return;
    if(g_passportFormat == FORMAT_SINGLE_NUMBER)
    {
        printf("ID: %d", id->series);
    }
    else if(g_passportFormat == FORMAT_SPACE_SEPARATED)
    {
        printf("Паспорт: %d %d", id->series, id->number);
    }
    else
    {
        printf("Паспорт: %d %d", id->series, id->number);
    }
}

void initPersonList(PersonArray* arr)
{
    arr->data = NULL;
    arr->size = 0;
}

void addPerson(PersonArray* arr, PersonBase* person)
{
    PersonBase** newData = (PersonBase**)realloc(arr->data, (arr->size + 1) * sizeof(PersonBase*));
    if (newData == NULL){
        printf("Ошибка выделения памяти.\n");
        return;
    }
    arr->data = newData;
    arr->data[arr->size] = person;
    arr->size++;
}

void removePerson(PersonArray* arr, int index)
{
    if (index < 0 || index >= arr->size){
        printf("Неверный индекс человека.\n");
        return;
    }
    
    PersonBase* p = arr->data[index];
    free(p->firstName);
    free(p->secondName);
    free(p->lastName);
    free(p);
    
    if (arr->size == 1)
    {
        free(arr->data);
        arr->data = NULL;
        arr->size = 0;
        printf("Последний человек удален. Массив пуст.\n");
        return;
    }
    
    if (arr->size == 1)
    {
        free(arr->data);
        arr->data = NULL;
    } 
    else{
        for (int i = index; i < arr->size - 1; i++)
        {
            arr->data[i] = arr->data[i + 1];
        }
        PersonBase** newData = (PersonBase**)realloc(arr->data, (arr->size - 1) * sizeof(PersonBase*));
        if (newData) arr->data = newData;
    }
    arr->size--;
    printf("Человек с индексом %d удален. Осталось: %d\n", index + 1, arr->size);
}

void freePersonArray(PersonArray* arr)
{
    if (arr->data != NULL){
        for (int i = 0; i < arr->size; i++)
        {
            PersonBase* p = arr->data[i];
            free(p->firstName);
            free(p->secondName);
            free(p->lastName);
            free(p);
        }
        free(arr->data);
        arr->data = NULL;
    }
    arr->size = 0;
}

int isStudent(PersonBase* p)
{
    return p && p->type == PERSON_STUDENT;
}

int isTeacher(PersonBase* p)
{
    return p && p->type == PERSON_TEACHER;
}

void printPerson(PersonBase* p)
{
    if (!p) return;
    
    if (isStudent(p)){
        Student* s = (Student*)p;
        printf("  [Студент] %s %s %s | Стипендия: %d | Дата рождения: %d.%d.%d\n",
               p->lastName, p->firstName, p->secondName,
               s->scholarship, p->dayBirth, p->monthBirth, p->yearBirth);
    }
    else if (isTeacher(p)){
        Teacher* t = (Teacher*)p;
        printf("  [Преподаватель] %s %s %s | ЗП: %d | Дата рождения: %d.%d.%d\n",
               p->lastName, p->firstName, p->secondName,
               t->salary, p->dayBirth, p->monthBirth, p->yearBirth);
    }
}

void printAllPersons(PersonArray* arr)

{
    if (!arr || arr->size == 0){
        printf("  (список пуст)\n");
        return;
    }
    for (int i = 0; i < arr->size; i++){
        printPerson(arr->data[i]);
    }
}

PersonBase* findPersonByID(PersonArray* arr, int series, int number)
{
    if (!arr || arr->data == NULL) return NULL;
    Person_ID searchID = {series, number};
    
    for (int i = 0; i < arr->size; i++){
        if (comparePassportIDs(&arr->data[i]->id, &searchID))
        {
            return arr->data[i];
        }
    }
    return NULL;
}

Student* findStudentByIndex(PersonArray* arr, int index)
{
    if (!arr || index < 0 || index >= arr->size) return NULL;
    PersonBase* p = arr->data[index];
    return isStudent(p) ? (Student*)p : NULL;
}

Teacher* findTeacherByIndex(PersonArray* arr, int index)
{
    if (!arr || index < 0 || index >= arr->size) return NULL;
    PersonBase* p = arr->data[index];
    return isTeacher(p) ? (Teacher*)p : NULL;
}