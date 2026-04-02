#ifndef TESTS_H
#define TESTS_H

#define COLOR_RED     "\033[0;31m"
#define COLOR_GREEN   "\033[0;32m"
#define COLOR_YELLOW  "\033[0;33m"
#define COLOR_RESET   "\033[0m"

#define TEST_START(name) \
    printf("Тест: %s ... ", name); \
    int test_failed_in_this = 0; \
    int test_errors_count = 0;

#define ASSERT(condition, message) \
    if (!(condition)) { \
        test_failed_in_this = 1; \
        test_errors_count++; \
        printf("\n  " COLOR_RED "? FAIL: " COLOR_RESET "%s", message); \
    }

#define TEST_PASS() \
    if (test_failed_in_this) { \
        tests_failed++; \
        printf("\n  " COLOR_RED "[FAILED] " COLOR_RESET "(Ошибок: %d)\n", test_errors_count); \
    } else { \
        tests_passed++; \
        printf(COLOR_GREEN "[PASS]" COLOR_RESET "\n"); \
    }

extern int tests_passed;
extern int tests_failed;

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
void test_createStudent(void);
void test_createStudent_nullInput(void);
void test_createStudent_memoryFailure(void);
void test_createTeacher(void);
void test_createTeacher_nullInput(void);
void test_createTeacher_memoryFailure(void);
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
void test_inputPassportID(void);
void test_inputFullName(void);
void test_selectPassportFormat(void);
void test_printmenu(void);
void test_VTable_getPayment(void);

int runAllTests(void);

#endif