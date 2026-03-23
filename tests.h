#ifndef TESTS_H
#define TESTS_H

#include "person.h"
#include "student.h"
#include "teacher.h"
#include "funcs.h"

// ============================================================
// Œ€Š‘› „‹Ÿ ’…‘’ˆ‚€ˆŸ
// ============================================================
#define TEST_START(name) printf("’¥áâ: %s... ", name)
#define TEST_PASS() { tests_passed++; printf("PASSED\n"); }
#define TEST_FAIL(msg) { tests_failed++; printf("FAILED: %s\n", msg); }
#define ASSERT(cond, msg) if (!(cond)) { TEST_FAIL(msg); return; }

// ƒ«®¡ «ì­ë¥ áçñâç¨ª¨
extern int tests_passed;
extern int tests_failed;

// ============================================================
// ’…‘’› „‹Ÿ person.c
// ============================================================
void test_setPassportFormat(void);
void test_getPassportFormat(void);
void test_comparePassportIDs(void);
void test_printPassportID(void);
void test_initPersonList(void);
void test_addPerson(void);
void test_removePerson(void);
void test_freePersonArray(void);
void test_isStudent_isTeacher(void);
void test_printPerson(void);
void test_printAllPersons(void);
void test_findPersonByID(void);
void test_findStudentByIndex(void);
void test_findTeacherByIndex(void);

// ============================================================
// ’…‘’› „‹Ÿ student.c
// ============================================================
void test_createStudent(void);
void test_createStudent_nullInput(void);
void test_createStudent_memoryFailure(void);

// ============================================================
// ’…‘’› „‹Ÿ teacher.c
// ============================================================
void test_createTeacher(void);
void test_createTeacher_nullInput(void);
void test_createTeacher_memoryFailure(void);

// ============================================================
// ’…‘’› „‹Ÿ funcs.c
// ============================================================
void test_addPrefixToPersonName(void);
void test_addPrefixToPersonName_nullInput(void);
void test_mapPersons(void);
void test_mapPersons_nullInput(void);
void test_mapPersons_emptyArray(void);
void test_concatPrint(void);
void test_concatPrint_nullInput(void);
void test_concatPrint_emptyArray(void);
void test_printStudentsOnly(void);
void test_printTeachersOnly(void);
void test_isValidName(void);
void test_isValidDate(void);

// ============================================================
// ’…‘’› „‹Ÿ main.c (®¡êï¢«¥­¨ï äã­ªæ¨©)
// ============================================================
void clearInputBuffer(void);
void printmenu(void);
void test_inputPassportID(void);
void test_inputFullName(void);
void test_selectPassportFormat(void);
void test_printmenu(void);

// ============================================================
// ‡€“‘Š ‚‘…• ’…‘’‚
// ============================================================
int runAllTests(void);

#endif 