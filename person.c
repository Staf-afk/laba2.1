#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"

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
