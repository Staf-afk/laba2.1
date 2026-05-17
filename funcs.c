#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcs.h"

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
        PersonBase copy;
    
        copy.firstName = original->firstName ? strdup(original->firstName) : strdup("");
        copy.secondName = original->secondName ? strdup(original->secondName) : strdup("");
        copy.lastName = original->lastName ? strdup(original->lastName) : strdup("");
        
        if(!copy.firstName || !copy.secondName || !copy.lastName){
            if(copy.firstName) free(copy.firstName);
            if(copy.secondName) free(copy.secondName);
            if(copy.lastName) free(copy.lastName);
            freePersonArray(result);
            free(result);
            return NULL;
        }
        copy.dayBirth = original->dayBirth;
        copy.monthBirth = original->monthBirth;
        copy.yearBirth = original->yearBirth;
        copy.id = original->id;
        copy.currency = original->currency;
        copy.getPayment = original->getPayment;
        copy.destroy = original->destroy;
        copy.comparePassport = original->comparePassport;
        copy.getFullName = original->getFullName;
        copy.toString = original->toString;
        
        if(mapper(&copy)){
            addPerson(result, &copy);
        }
        free(copy.firstName);
        free(copy.secondName);
        free(copy.lastName);
    }
    
    return result;
}

char* getPaymentString(PersonBase* p) {
    if (!p || !p->getPayment) {
        return strdup("Нет данных о выплате");
    }
    
    void* paymentPtr = p->getPayment(p);
    if (!paymentPtr) {
        return strdup("Ошибка получения выплаты");
    }
    
    unsigned int payment = *((unsigned int*)paymentPtr);
    char* currencySym = currencyToString(p->currency);
    
    size_t size = snprintf(NULL, 0, "Выплата: %u %s", payment, currencySym) + 1;
    char* result = malloc(size);
    if(result){
        sprintf(result, "Выплата: %u %s", payment, currencySym);
    }
    return result;
}

CodeError isValidName(char* name){
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

