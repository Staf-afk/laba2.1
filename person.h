#ifndef PERSON_H
#define PERSON_H

typedef enum {
    FORMAT_STRUCTURE = 0,
    FORMAT_SINGLE_NUMBER = 1,
    FORMAT_SPACE_SEPARATED = 2
} PassportFormat;

typedef struct {
    int series;
    int number;
} Person_ID;

typedef enum {
    PERSON_STUDENT = 1,
    PERSON_TEACHER = 2
} PersonType;

typedef struct {
    char* firstName;
    char* secondName;
    char* lastName;
    int dayBirth;
    int monthBirth;
    int yearBirth;
    Person_ID id;
    PersonType type;
} PersonBase;

typedef struct {
    PersonBase base;
    int scholarship;
} Student;

typedef struct {
    PersonBase base;
    int salary;
} Teacher;

typedef struct {
    PersonBase** data;
    int size;
} PersonArray;

extern PassportFormat g_passportFormat;

void setPassportFormat(PassportFormat format);
PassportFormat getPassportFormat(void);
int comparePassportIDs(Person_ID* id1, Person_ID* id2);
void printPassportID(Person_ID* id);

void initPersonList(PersonArray* arr);
void addPerson(PersonArray* arr, PersonBase* person);
void removePerson(PersonArray* arr, int index);
void freePersonArray(PersonArray* arr);
void printPerson(PersonBase* p);
void printAllPersons(PersonArray* arr);

PersonBase* findPersonByID(PersonArray* arr, int series, int number);
Student* findStudentByIndex(PersonArray* arr, int index);
Teacher* findTeacherByIndex(PersonArray* arr, int index);

int isStudent(PersonBase* p);
int isTeacher(PersonBase* p);

#endif