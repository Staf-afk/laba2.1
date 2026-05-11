#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcs.h"
#include "student.h"
#include "teacher.h"

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

PersonArray* mapPersons(PersonArray* arr, int (*mapper)(PersonBase*))
{
    if (!arr || !mapper) return NULL;
    
    PersonArray* result = malloc(sizeof(PersonArray));
    if (!result) return NULL;
    if(initPersonList(result) != ERROR_OK){
        free(result);
        return NULL;
    }
    
    for(size_t i = 0; i < arr->size; i++)
    {
        PersonBase* original = &arr->data[i];
        PersonBase* copy = NULL;
        
        if (isStudent(original))
        {
            Student* s = (Student*)original;
            copy = (PersonBase*)createStudent(
                original->firstName, original->secondName, original->lastName,
                original->dayBirth, original->monthBirth, original->yearBirth,
                &original->id, s->scholarship, original->currency
            );
        }
        else if (isTeacher(original))
        {
            Teacher* t = (Teacher*)original;
            copy = (PersonBase*)createTeacher(
                original->firstName, original->secondName, original->lastName,
                original->dayBirth, original->monthBirth, original->yearBirth,
                &original->id, t->salary, original->currency
            );
        }
        if (copy){
            mapper(copy);
            addPerson(result, copy);
            free(copy->firstName);
            free(copy->secondName);
            free(copy->lastName);
            free(copy);
        }
    }
    
    return result;
}

void concatPrint(PersonArray* persons)
{
    printf("\n=== ОБЪЕДИНЁННЫЙ СПИСОК ===\n");
    if (!persons || persons->size == 0){
        printf("  (список пуст)\n");
        return;
    }
    
    printf("  -- Студенты:\n");
    size_t studentCount = 0;
    for (size_t i = 0; i < persons->size; i++)
    {
        if (isStudent(&persons->data[i]))
        {
            printf("%zu", studentCount + 1);
            printPerson(&persons->data[i]);
            studentCount++;
        }
    }
    if (studentCount == 0) printf("  (нет студентов)\n");
    
    printf("  -- Преподаватели:\n");
    size_t teacherCount = 0;
    for (size_t i = 0; i < persons->size; i++)
    {
        if (isTeacher(&persons->data[i])){
            printf("%zu", studentCount + teacherCount + 1);
            printPerson(&persons->data[i]);
            teacherCount++;
        }
    }
    if (teacherCount == 0) printf("  (нет преподавателей)\n");
    
    printf("  Итого: %zu человек\n", persons->size);
}

void printStudentsOnly(PersonArray* arr)
{
    printf("\n=== СТУДЕНТЫ ===\n");
    size_t count = 0;
    if (!arr || arr->size == 0){
        printf("  (список пуст)\n");
        return;
    }
    for (size_t i = 0; i < arr->size; i++)
    {
        if (isStudent(&arr->data[i]))
        {
            printPerson(&arr->data[i]);
            count++;
        }
    }
    if (count == 0) printf("  (нет студентов)\n");
    else printf("  Всего студентов: %zu\n", count);
}

void printTeachersOnly(PersonArray* arr)
{
    printf("\n=== ПРЕПОДАВАТЕЛИ ===\n");
    size_t count = 0;
    if (!arr || arr->size == 0)
    {
        printf("  (список пуст)\n");
        return;
    }
    for (size_t i = 0; i < arr->size; i++)
    {
        if (isTeacher(&arr->data[i]))
        {
            printPerson(&arr->data[i]);
            count++;
        }
    }
    if (count == 0)
    {
        printf("  (нет преподавателей)\n");
    }
    else
    { 
        printf("  Всего преподавателей: %zu\n", count);
    }
}

CodeError isValidName( char* name){
    if(!name || strlen(name) == 0) return ERROR_INVALID_NAME;
    if(strlen(name) > 50) return ERROR_INVALID_NAME;
    
    for(int i = 0; name[i]; i++){
        if(isdigit((unsigned char)name[i])) return ERROR_INVALID_NAME;
    }
    return ERROR_OK;
}

CodeError isValidDate(uint8_t day, uint8_t month, uint16_t year){
    if(day < 1 || day > 31) return ERROR_INVALID_DATE;
    if(month < 1 || month > 12) return ERROR_INVALID_DATE;
    if(year < 1920 || year > 2010) return ERROR_INVALID_DATE;
    
    if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) 
        return ERROR_INVALID_DATE;
    
    if(month == 2){
        int isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if(day > (isLeap ? 29 : 28)) return ERROR_INVALID_DATE;
    }
    
    return ERROR_OK;
}


void printPersonPayment(PersonBase* p) {
    if (!p || !p->getPayment) {
        printf("  Нет данных о выплате\n");
        return;
    }
    
    // Отладка: выводим сырой указатель
    void* rawPtr = p->getPayment(p);
    printf("  DEBUG: raw pointer = %p\n", rawPtr);
    
    // Читаем как unsigned int
    unsigned int payment = *((unsigned int*)rawPtr);
    printf("  DEBUG: payment as unsigned int = %u\n", payment);
    
    // Читаем как int (для сравнения)
    int paymentSigned = *((int*)rawPtr);
    printf("  DEBUG: payment as int = %d\n", paymentSigned);
    
    const char* currencySym = currencyToString(p->currency);
    
    if (isStudent(p)) {
        printf("  Стипендия: %u %s\n", payment, currencySym);
    } 
    else if (isTeacher(p)) {
        printf("  Зарплата: %u %s\n", payment, currencySym);
    }
}
