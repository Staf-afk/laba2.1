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

int comparePassportIDs(Person_ID* id1, Person_ID* id2){
    if(!id1 || !id2) return 0;
    if(g_passportFormat == FORMAT_SINGLE_NUMBER){
        return (id1->series == id2->series);
    }
    else{
        return (id1->series == id2->series && id1->number == id2->number);
    }
}

CodeError initPersonList(PersonArray* arr){
    if(!arr) return ERROR_NULL_POINTER;
    arr->data = NULL;
    arr->size = 0;
    return ERROR_OK;
}

CodeError addPerson(PersonArray* arr, PersonBase* person){
    if(!arr || !person) return ERROR_NULL_POINTER;
    PersonBase* newData = realloc(arr->data, (arr->size + 1) * sizeof(Teacher));
    if(!newData) return ERROR_MEMORY_ALLOCATION;
    arr->data = newData;
    PersonBase* dest = (PersonBase*)((char*)arr->data + arr->size * sizeof(Teacher));
    
    dest->firstName = person->firstName ? strdup(person->firstName) : strdup("");
    dest->secondName = person->secondName ? strdup(person->secondName) : strdup("");
    dest->lastName = person->lastName ? strdup(person->lastName) : strdup("");
    if(!dest->firstName || !dest->secondName || !dest->lastName){
        if(dest->firstName) free(dest->firstName);
        if(dest->secondName) free(dest->secondName);
        if(dest->lastName) free(dest->lastName);
        return ERROR_MEMORY_ALLOCATION;
    }
    dest->dayBirth = person->dayBirth;
    dest->monthBirth = person->monthBirth;
    dest->yearBirth = person->yearBirth;
    dest->id = person->id;
    dest->currency = person->currency;
    dest->getPayment = person->getPayment;
    dest->destroy = person->destroy;
    dest->comparePassport = person->comparePassport;
    dest->getFullName = person->getFullName;
    dest->toString = person->toString;
    *((unsigned int*)((char*)dest + sizeof(PersonBase))) = *((unsigned int*)((char*)person + sizeof(PersonBase)));
    
    arr->size++;
    return ERROR_OK;
}


CodeError removePerson(PersonArray* arr, size_t index){
    if(!arr) return ERROR_NULL_POINTER;
    if(arr->size == 0) return ERROR_EMPTY_LIST;
    if(index >= arr->size) return ERROR_INVALID_INDEX;
    if(arr->data[index].destroy){
        arr->data[index].destroy(&arr->data[index]);
    }
    if(arr->data[index].firstName) free(arr->data[index].firstName);
    if(arr->data[index].secondName) free(arr->data[index].secondName);
    if(arr->data[index].lastName) free(arr->data[index].lastName);
    
    for(size_t i = index; i < arr->size - 1; i++){
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
    if(arr->size > 0){
        PersonBase* newData = realloc(arr->data, arr->size * sizeof(PersonBase));
        if(newData){
            arr->data = newData;
        }
    } else {
        free(arr->data);
        arr->data = NULL;
    }
    
    return ERROR_OK;
}

void freePersonArray(PersonArray* arr){
    if(!arr) return;
    for(size_t i = 0; i < arr->size; i++){
        if(arr->data[i].destroy){
            arr->data[i].destroy(&arr->data[i]);
        }
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

PersonBase* findPersonByID(PersonArray* arr, unsigned int series, unsigned int number){
    if (!arr || arr->size == 0) return NULL;
    Person_ID searchID = {series, number};
    
    for (size_t i = 0; i < arr->size; i++){
        if(arr->data[i].comparePassport){
            if(arr->data[i].comparePassport(&arr->data[i], &searchID)){
                return &arr->data[i];
            }
        }
    }
    return NULL;
}

char* currencyToString(CurrencyType currency){
    if (currency == CURRENCY_USD) {
        return "USD";
    }
    return "RUB";
}