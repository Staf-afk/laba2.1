#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tests.h"
#include "teacher.h"
#include "student.h"
#include "funcs.h"

StudentArray students;
TeacherArray teachers;

void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printmenu(){
    printf(
        "========МЕНЮ=======\n"
        "[1] - Добавить преподавателя.\n"
        "[2] - Добавить студента.\n"
        "[3] - Удалить преподавателя.\n"
        "[4] - Удалить студента.\n"
        "[5] - Найти человека по ID.\n"
        "[6] - Вывести список студентов.\n"
        "[7] - Вывести список преподавателей.\n"
        "[8] - Вывести всех.\n"    //сойдет за конкатенацию
        "[9] - Добавить префикс к именам.\n"   //сойдет за map
        "[10] - Запустить тесты.\n"
        "[0] - Завершить программу.\n"
        "Выбор: "
    );
}

void inputPassportID(Person_ID* id){
    int format;
    printf("Выберите формат ввода паспорта:\n");
    printf("  [1] - Серия и номер отдельно\n");
    printf("  [2] - В одну строку через пробел\n");
    printf("Выбор: ");
    scanf("%d", &format);
    clearInputBuffer();

        if(format == 1){
            printf("Введите серию паспорта: ");
            scanf("%d", &id->series);
            clearInputBuffer();
            printf("Введите номер паспорта: ");
            scanf("%d", &id->number);
            clearInputBuffer();
        }
        else if(format == 2){
            printf("Введите серию и номер через пробел: ");
            scanf("%d %d", &id->series, &id->number);
            clearInputBuffer();
        }
        else{
            printf("Неверный выбор, используется формат по умолчанию (отдельно).\n");
            printf("Введите серию паспорта: ");
            scanf("%d", &id->series);
            clearInputBuffer();
            printf("Введите номер паспорта: ");
            scanf("%d", &id->number);
            clearInputBuffer();
        }
}

void inputFullName(char* firstName, char* secondName, char* lastName){
    printf("Введите имя: ");
    scanf("%49s", firstName);
    clearInputBuffer();
    printf("Введите отчество: ");
    scanf("%49s", secondName);
    clearInputBuffer();
    printf("Введите фамилию: ");
    scanf("%49s", lastName);
    clearInputBuffer();
}

int main(void){
    int choice = 1;
    char firstName[50], secondName[50], lastName[50];
    int dayStudentBirth = 0, monthStudentBirth = 0, yearStudentBirth = 0;
    int dayTeacherBirth = 0, monthTeacherBirth = 0, yearTeacherBirth = 0;
    int salary, scholarship;
    int index;
    Person_ID id;
    initStudentList(&students);
    initTeacherList(&teachers);

    while(choice != 0){
        printmenu();
        scanf("%d",&choice);
        clearInputBuffer();
        switch (choice){

        case 1:{
            printf("\n--- Добавление преподавателя ---\n");
            inputPassportID(&id);
            inputFullName(firstName, secondName, lastName);
            printf("Введите дату рождения (день месяц год P.S. через пробел в формате XX XX XXXX): ");
            scanf("%d %d %d", &dayTeacherBirth, &monthTeacherBirth, &yearTeacherBirth);
            clearInputBuffer();
            printf("Введите зарплату: ");
            scanf("%d", &salary);
            clearInputBuffer();

            addTeacher(&teachers, firstName, secondName, lastName, dayTeacherBirth, monthTeacherBirth, yearTeacherBirth, (Teacher_ID*)&id, salary);
            printf("Преподаватель добавлен.\n\n");
            break;
        }

        case 2:{
            printf("\n--- Добавление студента ---\n");
            inputPassportID(&id);
            inputFullName(firstName, secondName, lastName);
            printf("Введите дату рождения (день месяц год P.S. через пробел в формате XX XX XXXX): ");
            scanf("%d %d %d", &dayStudentBirth, &monthStudentBirth, &yearStudentBirth);
            clearInputBuffer();
            printf("Введите стипендию: ");
            scanf("%d", &scholarship);
            clearInputBuffer();

            addStudent(&students, firstName, secondName, lastName, dayStudentBirth, monthStudentBirth, yearStudentBirth, (Student_ID*)&id, scholarship);
            printf("Студент добавлен.\n\n");
            break;
        }

        case 3:{
            printf("\nВведите индекс преподавателя для удаления: ");
            scanf("%d", &index);
            clearInputBuffer();
            removeTeacher(&teachers, index - 1);
            printf("\n");
            break;
        }

        case 4:{
            printf("\nВведите индекс студента для удаления: ");
            scanf("%d", &index);
            clearInputBuffer();
            removeStudent(&students, index - 1);
            printf("\n");
            break;
        }

        case 5:{
            printf("\n--- Поиск по паспортным данным ---\n");
            inputPassportID(&id);
            findPersonByID(&students, &teachers, id.series, id.number);
            printf("\n");
            break;
        }

        case 6:
            printf("\n");
            printAllStudents(&students);
            printf("\n");
            break;
        case 7:
            printf("\n");
            printAllTeachers(&teachers);
            printf("\n");
            break;
        case 8:
            printf("\n");
            concatPrint(&students, &teachers);
            printf("\n");
            break;

        case 9:{
            StudentArray* mappedStudents = mapStudents(&students, addPrefixToStudentName);
            TeacherArray* mappedTeachers = mapTeachers(&teachers, addPrefixToTeacherName);
            printf("\nПрефикс добавлен к именам.\n");
            concatPrint(mappedStudents, mappedTeachers);
            freeStudentArray(mappedStudents);
            freeTeacherArray(mappedTeachers);
            free(mappedStudents);
            free(mappedTeachers);
            printf("\n");
            break;
        }

        case 10:
            printf("\nТесты запущены.\n\n");
            break;

        case 0:
            printf("Завершение работы.\n");
            freeStudentArray(&students);
            freeTeacherArray(&teachers);
            break;
        
        default:
            printf("Неверный выбор.\n\n");
            break;
        }
    }
    return 0;
}