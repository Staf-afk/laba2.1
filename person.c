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


char* errorInWords(CodeError error){
    switch(error){
        case ERROR_OK:                 return "Успешно";
        case ERROR_MEMORY_ALLOCATION:  return "Ошибка выделения памяти";
        case ERROR_NULL_POINTER:       return "NULL указатель";
        case ERROR_INVALID_INDEX:      return "Неверный индекс";
        case ERROR_EMPTY_LIST:         return "Список пуст";
        case ERROR_INVALID_NAME:       return "Некорректное имя";
        case ERROR_INVALID_DATE:       return "Некорректная дата";
        case ERROR_NOT_FOUND:          return "Элемент не найден";
        case ERROR_MAPPER_FAILED:      return "Ошибка преобразования";
        default:                       return "Неизвестная ошибка";
    }
}

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
    if(g_passportFormat == FORMAT_SINGLE_NUMBER)
    {
        return (id1->series == id2->series);
    }
    else{
        return (id1->series == id2->series && id1->number == id2->number);
    }
}




/*===========================================
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||             РЕКЛАМА                      ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
=============================================*/

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



CodeError initPersonList(PersonArray* arr){
    if(!arr) return ERROR_NULL_POINTER;
    arr->data = NULL;
    arr->size = 0;
    return ERROR_OK;
}

CodeError addPerson(PersonArray* arr, PersonBase* person) {
    if(!arr || !person) return ERROR_NULL_POINTER;
    void* newData = realloc(arr->data, (arr->size + 1) * sizeof(PersonBase));
    if(!newData) return ERROR_MEMORY_ALLOCATION;
    arr->data = newData;

    PersonBase* dest = &arr->data[arr->size];

    if (isStudent(person)) {
        Student* src = (Student*)person;
        Student* dst = (Student*)dest;
        dst->base.firstName = src->base.firstName ? strdup(src->base.firstName) : strdup("");
        dst->base.secondName = src->base.secondName ? strdup(src->base.secondName) : strdup("");
        dst->base.lastName = src->base.lastName ? strdup(src->base.lastName) : strdup("");
        
        if(!dst->base.firstName || !dst->base.secondName || !dst->base.lastName) {
            free(dst->base.firstName); free(dst->base.secondName); free(dst->base.lastName);
            return ERROR_MEMORY_ALLOCATION;
        }
        dst->base.dayBirth = src->base.dayBirth;
        dst->base.monthBirth = src->base.monthBirth;
        dst->base.yearBirth = src->base.yearBirth;
        dst->base.id = src->base.id;
        dst->base.type = src->base.type;
        dst->base.currency = src->base.currency;
        dst->base.getPayment = src->base.getPayment;
        dst->scholarship = src->scholarship;
    }
    else if (isTeacher(person)) {
        Teacher* src = (Teacher*)person;
        Teacher* dst = (Teacher*)dest;
        dst->base.firstName = src->base.firstName ? strdup(src->base.firstName) : strdup("");
        dst->base.secondName = src->base.secondName ? strdup(src->base.secondName) : strdup("");
        dst->base.lastName = src->base.lastName ? strdup(src->base.lastName) : strdup("");
        
        if(!dst->base.firstName || !dst->base.secondName || !dst->base.lastName) {
            free(dst->base.firstName); free(dst->base.secondName); free(dst->base.lastName);
            return ERROR_MEMORY_ALLOCATION;
        }
        dst->base.dayBirth = src->base.dayBirth;
        dst->base.monthBirth = src->base.monthBirth;
        dst->base.yearBirth = src->base.yearBirth;
        dst->base.id = src->base.id;
        dst->base.type = src->base.type;
        dst->base.currency = src->base.currency;
        dst->base.getPayment = src->base.getPayment;
        dst->salary = src->salary;
    }
    
    arr->size++;
    return ERROR_OK;
}


/*===========================================
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||             РЕКЛАМА                      ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
=============================================*/

CodeError removePerson(PersonArray* arr, size_t index){
    if(!arr) return ERROR_NULL_POINTER;
    if(arr->size == 0) return ERROR_EMPTY_LIST;
    if(index >= arr->size) return ERROR_INVALID_INDEX;

    if(arr->data[index].firstName) free(arr->data[index].firstName);
    if(arr->data[index].secondName) free(arr->data[index].secondName);
    if(arr->data[index].lastName) free(arr->data[index].lastName);

    for(size_t i = index; i < arr->size - 1; i++){
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;

    if(arr->size == 0){
        free(arr->data);
        arr->data = NULL;
    } 
    else{
        PersonBase* newData = (PersonBase*)realloc(arr->data, arr->size * sizeof(PersonBase));
        if(newData){
            arr->data = newData;
        }
    }
    return ERROR_OK;
}

/*===========================================
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||             РЕКЛАМА                      ||
||                                          ||
||               ЫАЕЫАЕЫА                   ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
=============================================*/

void freePersonArray(PersonArray* arr)
{
    if(!arr) return;
    for(size_t i = 0; i < arr->size; i++){
        if(arr->data[i].firstName) free(arr->data[i].firstName);
        if(arr->data[i].secondName) free(arr->data[i].secondName);
        if(arr->data[i].lastName) free(arr->data[i].lastName);
    }
    if(arr->data){
        free(arr->data);
        arr->data = NULL;
    }
    arr->size = 0;
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

    void* paymentPtr = p->getPayment(p);
    unsigned int payment;
    if (paymentPtr != NULL){
        payment = *((unsigned int*)paymentPtr);
    } 
    else{
        payment = 0;
    }
    char* currencySym = currencyToString(p->currency);
    
    if (isStudent(p)){
        Student* s = (Student*)p;
        printf("  [Студент] %s %s %s | Стипендия: %u %s | Дата рождения: %hhu.%hhu.%hu\n",
               p->lastName, p->firstName, p->secondName,
               s->scholarship, currencySym,
               p->dayBirth, p->monthBirth, p->yearBirth);
    }
    else if (isTeacher(p)){
        Teacher* t = (Teacher*)p;
        printf("  [Преподаватель] %s %s %s | ЗП: %u %s | Дата рождения: %hhu.%hhu.%hu\n",
               p->lastName, p->firstName, p->secondName,
               t->salary, currencySym,
               p->dayBirth, p->monthBirth, p->yearBirth);
    }
}

void printAllPersons(PersonArray* arr)
{
    if (!arr || arr->size == 0){
        printf("  (список пуст)\n");
        return;
    }
    for (size_t i = 0; i < arr->size; i++){
        printPerson(&arr->data[i]);
    }
}

/*===========================================
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||             РЕКЛАМА                      ||
||             ИИКС                         ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
=============================================*/

PersonBase* findPersonByID(PersonArray* arr, unsigned int series, unsigned int number)
{
    if (!arr || arr->size == 0) return NULL;
    Person_ID searchID = {series, number};
    
    for (size_t i = 0; i < arr->size; i++){
        if (comparePassportIDs(&arr->data[i].id, &searchID))
        {
            return &arr->data[i];
        }
    }
    return NULL;
}

Student* findStudentByIndex(PersonArray* arr, size_t index)
{
    if (!arr || index >= arr->size) return NULL;
    PersonBase* p = &arr->data[index];
    return isStudent(p) ? (Student*)p : NULL;
}

Teacher* findTeacherByIndex(PersonArray* arr, size_t index)
{
    if (!arr || index >= arr->size) return NULL;
    PersonBase* p = &arr->data[index];
    return isTeacher(p) ? (Teacher*)p : NULL;
}

char* currencyToString(CurrencyType currency)
{
    if (currency == CURRENCY_USD) {
        return "USD";
    }
    return "RUB";
}

/*===========================================
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||             РЕКЛАМА                      ||
||                                          ||
||               1 Х ВЕТ                    ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
||                                          ||
=============================================*/