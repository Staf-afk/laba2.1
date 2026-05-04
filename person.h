#ifndef PERSON_H
#define PERSON_H
#include <inttypes.h>

typedef enum{
    ERROR_OK = 0,
    ERROR_MEMORY_ALLOCATION = -1,
    ERROR_NULL_POINTER = -2,
    ERROR_INVALID_INDEX = -3,
    ERROR_EMPTY_LIST = -4,
    ERROR_INVALID_NAME = -5,
    ERROR_INVALID_DATE = -6,
    ERROR_NOT_FOUND = -7,
    ERROR_MAPPER_FAILED = -8
} CodeError;

const char* errorInWords(CodeError error);

typedef enum{
    FORMAT_STRUCTURE,
    FORMAT_SINGLE_NUMBER,
    FORMAT_SPACE_SEPARATED
} PassportFormat;


typedef struct{
    int series;
    int number;
} Person_ID;


typedef enum {
    PERSON_STUDENT = 1,
    PERSON_TEACHER = 2
} PersonType;

typedef enum {
    PAYMENT_TYPE_INT,
    PAYMENT_TYPE_DOUBLE
} PaymentType;


typedef struct PersonBase{
    char* firstName;
    char* secondName;
    char* lastName;
    uint8_t dayBirth;
    uint8_t monthBirth;
    uint8_t yearBirth;
    Person_ID id;
    PersonType type;
    void* (*getPayment)(struct PersonBase* self);
} PersonBase;

/*================================================
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||   ‡„…‘œ Œƒ‹€ › ›’œ ‚€˜€ …Š‹€Œ€,           ||
||           ‡€  „ €‹‹› ‡€ ‹€“               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
==================================================*/

typedef struct {
    PersonBase base;
    int scholarship;
} Student;


typedef struct {
    PersonBase base;
    int salary;
} Teacher;

/*================================================
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||   ‡„…‘œ Œƒ‹€ › ›’œ ‚€˜€ …Š‹€Œ€,           ||
||           ‡€  „ €‹‹› ‡€ ‹€“               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
||                                               ||
==================================================*/

typedef struct {
    PersonBase** data;
    int size;
} PersonArray;


extern PassportFormat g_passportFormat;


void setPassportFormat(PassportFormat format);

PassportFormat getPassportFormat(void);

int comparePassportIDs(Person_ID* id1, Person_ID* id2);

void printPassportID(Person_ID* id);




CodeError  initPersonList(PersonArray* arr);

CodeError  addPerson(PersonArray* arr, PersonBase* person);

CodeError removePerson(PersonArray* arr, int index);

void freePersonArray(PersonArray* arr);

void printPerson(PersonBase* p);

void printAllPersons(PersonArray* arr);



PersonBase* findPersonByID(PersonArray* arr, int series, int number);

Student* findStudentByIndex(PersonArray* arr, int index);

Teacher* findTeacherByIndex(PersonArray* arr, int index);



int isStudent(PersonBase* p);

int isTeacher(PersonBase* p);


#endif