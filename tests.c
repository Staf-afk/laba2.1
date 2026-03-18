#include "tests.h"

// Глобальные счетчики
int testsPassed = 0;
int testsFailed = 0;
int testsTotal = 0;

// ============================================================
// ТЕСТЫ СТУДЕНТОВ (student.c)
// ============================================================

TEST(StudentInit) {
    StudentArray arr;
    initStudentList(&arr);
    ASSERT_NULL(arr.data);
    ASSERT_EQ_INT(arr.size, 0);
    TEST_PASS();
}

TEST(StudentAddSingle) {
    StudentArray arr;
    initStudentList(&arr);
    
    Person_ID id = {1234, 567890};
    addStudent(&arr, "Иван", "Иванович", "Иванов", 1, 1, 2000, (Student_ID*)&id, 5000);
    
    ASSERT_EQ_INT(arr.size, 1);
    ASSERT_EQ_STR(arr.data[0].firstName, "Иван");
    ASSERT_EQ_STR(arr.data[0].lastName, "Иванов");
    ASSERT_EQ_INT(arr.data[0].scholarship, 5000);
    
    freeStudentArray(&arr);
    TEST_PASS();
}

TEST(StudentAddMultiple) {
    StudentArray arr;
    initStudentList(&arr);
    
    Person_ID id1 = {1111, 111};
    Person_ID id2 = {2222, 222};
    
    addStudent(&arr, "Студент1", "Отчество1", "Фамилия1", 1, 1, 2000, (Student_ID*)&id1, 1000);
    addStudent(&arr, "Студент2", "Отчество2", "Фамилия2", 2, 2, 2001, (Student_ID*)&id2, 2000);
    
    ASSERT_EQ_INT(arr.size, 2);
    ASSERT_EQ_STR(arr.data[0].firstName, "Студент1");
    ASSERT_EQ_STR(arr.data[1].firstName, "Студент2");
    
    freeStudentArray(&arr);
    TEST_PASS();
}

TEST(StudentRemoveFirst) {
    StudentArray arr;
    initStudentList(&arr);
    
    Person_ID id1 = {1111, 111};
    Person_ID id2 = {2222, 222};
    
    addStudent(&arr, "S1", "O1", "F1", 1, 1, 2000, (Student_ID*)&id1, 1000);
    addStudent(&arr, "S2", "O2", "F2", 1, 1, 2000, (Student_ID*)&id2, 2000);
    
    removeStudent(&arr, 0);
    
    ASSERT_EQ_INT(arr.size, 1);
    ASSERT_EQ_STR(arr.data[0].firstName, "S2");
    
    freeStudentArray(&arr);
    TEST_PASS();
}

TEST(StudentRemoveLast) {
    StudentArray arr;
    initStudentList(&arr);
    
    Person_ID id1 = {1111, 111};
    Person_ID id2 = {2222, 222};
    
    addStudent(&arr, "S1", "O1", "F1", 1, 1, 2000, (Student_ID*)&id1, 1000);
    addStudent(&arr, "S2", "O2", "F2", 1, 1, 2000, (Student_ID*)&id2, 2000);
    
    removeStudent(&arr, 1);
    
    ASSERT_EQ_INT(arr.size, 1);
    ASSERT_EQ_STR(arr.data[0].firstName, "S1");
    
    freeStudentArray(&arr);
    TEST_PASS();
}

TEST(StudentRemoveInvalidIndex) {
    StudentArray arr;
    initStudentList(&arr);
    
    Person_ID id = {1111, 111};
    addStudent(&arr, "S1", "O1", "F1", 1, 1, 2000, (Student_ID*)&id, 1000);
    
    removeStudent(&arr, 10); 
    ASSERT_EQ_INT(arr.size, 1);
    
    removeStudent(&arr, -1);
    ASSERT_EQ_INT(arr.size, 1);
    
    freeStudentArray(&arr);
    TEST_PASS();
}

TEST(StudentRemoveOnlyElement) {
    StudentArray arr;
    initStudentList(&arr);
    
    Person_ID id = {1111, 111};
    addStudent(&arr, "S1", "O1", "F1", 1, 1, 2000, (Student_ID*)&id, 1000);
    
    removeStudent(&arr, 0);
    
    ASSERT_EQ_INT(arr.size, 0);
    ASSERT_NULL(arr.data);
    
    TEST_PASS();
}

TEST(StudentFreeEmpty) {
    StudentArray arr;
    initStudentList(&arr);
    freeStudentArray(&arr);
    ASSERT_EQ_INT(arr.size, 0);
    TEST_PASS();
}

// ============================================================
// ТЕСТЫ ПРЕПОДАВАТЕЛЕЙ (teacher.c)
// ============================================================

TEST(TeacherInit) {
    TeacherArray arr;
    initTeacherList(&arr);
    ASSERT_NULL(arr.data);
    ASSERT_EQ_INT(arr.size, 0);
    TEST_PASS();
}

TEST(TeacherAddSingle) {
    TeacherArray arr;
    initTeacherList(&arr);
    
    Person_ID id = {5555, 666666};
    addTeacher(&arr, "Петр", "Петрович", "Петров", 5, 5, 1980, (Teacher_ID*)&id, 50000);
    
    ASSERT_EQ_INT(arr.size, 1);
    ASSERT_EQ_STR(arr.data[0].firstName, "Петр");
    ASSERT_EQ_INT(arr.data[0].salary, 50000);
    
    freeTeacherArray(&arr);
    TEST_PASS();
}

TEST(TeacherRemoveBasic) {
    TeacherArray arr;
    initTeacherList(&arr);
    
    Person_ID id1 = {1111, 111};
    Person_ID id2 = {2222, 222};
    
    addTeacher(&arr, "T1", "O1", "F1", 1, 1, 1980, (Teacher_ID*)&id1, 10000);
    addTeacher(&arr, "T2", "O2", "F2", 1, 1, 1980, (Teacher_ID*)&id2, 20000);
    
    removeTeacher(&arr, 0);
    
    ASSERT_EQ_INT(arr.size, 1);
    ASSERT_EQ_STR(arr.data[0].firstName, "T2");
    
    freeTeacherArray(&arr);
    TEST_PASS();
}

// ============================================================
// ТЕСТЫ ФУНКЦИЙ (funcs.c)
// ============================================================

TEST(FuncPrefixStudent) {
    StudentArray arr;
    initStudentList(&arr);
    Person_ID id = {1111, 111};
    addStudent(&arr, "Имя", "Отчество", "Фамилия", 1, 1, 2000, (Student_ID*)&id, 1000);
    
    int result = addPrefixToStudentName(&arr.data[0]);
    
    ASSERT_EQ_INT(result, 1);
    ASSERT_TRUE(strlen(arr.data[0].firstName) > strlen("Имя"));
    ASSERT_TRUE(strstr(arr.data[0].firstName, "[префикс]") != NULL);
    
    freeStudentArray(&arr);
    TEST_PASS();
}

TEST(FuncPrefixNullSafety) {
    int result = addPrefixToStudentName(NULL);
    ASSERT_EQ_INT(result, 0);
    
    Student s = {0};
    s.firstName = NULL;
    result = addPrefixToStudentName(&s);
    ASSERT_EQ_INT(result, 0);
    
    TEST_PASS();
}

TEST(FuncMapStudents) {
    StudentArray arr;
    initStudentList(&arr);
    Person_ID id = {1111, 111};
    addStudent(&arr, "Original", "O", "F", 1, 1, 2000, (Student_ID*)&id, 1000);
    
    StudentArray* mapped = mapStudents(&arr, addPrefixToStudentName);
    
    ASSERT_NOT_NULL(mapped);
    ASSERT_EQ_INT(mapped->size, 1);
    ASSERT_TRUE(strstr(mapped->data[0].firstName, "[префикс]") != NULL);
    ASSERT_TRUE(strstr(arr.data[0].firstName, "[префикс]") == NULL);
    
    freeStudentArray(&arr);
    freeStudentArray(mapped);
    free(mapped);
    TEST_PASS();
}

TEST(FuncMapNullSafety) {
    StudentArray* result = mapStudents(NULL, addPrefixToStudentName);
    ASSERT_NULL(result);
    
    StudentArray arr;
    initStudentList(&arr);
    result = mapStudents(&arr, NULL);
    ASSERT_NULL(result);
    
    TEST_PASS();
}

TEST(FuncFindStudentByID) {
    StudentArray arr;
    initStudentList(&arr);
    
    Person_ID id1 = {1234, 567890};
    Person_ID id2 = {9999, 000000};
    
    addStudent(&arr, "S1", "O1", "F1", 1, 1, 2000, (Student_ID*)&id1, 1000);
    addStudent(&arr, "S2", "O2", "F2", 1, 1, 2000, (Student_ID*)&id2, 2000);
    
    Student* found = findStudentByID(&arr, 1234, 567890);
    ASSERT_NOT_NULL(found);
    ASSERT_EQ_STR(found->firstName, "S1");
    
    Student* notFound = findStudentByID(&arr, 0000, 111111);
    ASSERT_NULL(notFound);
    
    freeStudentArray(&arr);
    TEST_PASS();
}

TEST(FuncFindTeacherByID) {
    TeacherArray arr;
    initTeacherList(&arr);
    
    Person_ID id = {5555, 666666};
    addTeacher(&arr, "T1", "O1", "F1", 1, 1, 1980, (Teacher_ID*)&id, 10000);
    
    Teacher* found = findTeacherByID(&arr, 5555, 666666);
    ASSERT_NOT_NULL(found);
    ASSERT_EQ_STR(found->firstName, "T1");
    
    freeTeacherArray(&arr);
    TEST_PASS();
}

TEST(FuncConcatPrint) {
    StudentArray sArr;
    TeacherArray tArr;
    initStudentList(&sArr);
    initTeacherList(&tArr);
    
    concatPrint(&sArr, &tArr);
    
    Person_ID sid = {1, 1};
    Person_ID tid = {2, 2};
    addStudent(&sArr, "S", "O", "F", 1, 1, 2000, (Student_ID*)&sid, 100);
    addTeacher(&tArr, "T", "O", "F", 1, 1, 1980, (Teacher_ID*)&tid, 1000);
    
    concatPrint(&sArr, &tArr);
    
    freeStudentArray(&sArr);
    freeTeacherArray(&tArr);
    TEST_PASS();
}

TEST(FuncMapEmptyArray) {
    StudentArray arr;
    initStudentList(&arr);
    
    StudentArray* mapped = mapStudents(&arr, addPrefixToStudentName);
    ASSERT_NOT_NULL(mapped);
    ASSERT_EQ_INT(mapped->size, 0);
    ASSERT_NULL(mapped->data);
    
    free(mapped);
    TEST_PASS();
}

// ============================================================
// ТЕСТЫ ПАМЯТИ (Memory Safety)
// ============================================================

TEST(MemoryDoubleFreeStudent) {
    StudentArray arr;
    initStudentList(&arr);
    Person_ID id = {1, 1};
    addStudent(&arr, "S", "O", "F", 1, 1, 2000, (Student_ID*)&id, 100);
    
    freeStudentArray(&arr);
    freeStudentArray(&arr);
    TEST_PASS();
}

TEST(MemoryDoubleFreeTeacher) {
    TeacherArray arr;
    initTeacherList(&arr);
    Person_ID id = {1, 1};
    addTeacher(&arr, "T", "O", "F", 1, 1, 1980, (Teacher_ID*)&id, 100);
    
    freeTeacherArray(&arr);
    freeTeacherArray(&arr);
    TEST_PASS();
}

// ============================================================
// ЗАПУСК ВСЕХ ТЕСТОВ
// ============================================================

void runAllTests(void) {
    TEST_INIT();
    
    printf("--- Тесты Студентов ---\n");
    RUN_TEST(StudentInit);
    RUN_TEST(StudentAddSingle);
    RUN_TEST(StudentAddMultiple);
    RUN_TEST(StudentRemoveFirst);
    RUN_TEST(StudentRemoveLast);
    RUN_TEST(StudentRemoveInvalidIndex);
    RUN_TEST(StudentRemoveOnlyElement);
    RUN_TEST(StudentFreeEmpty);
    
    printf("\n--- Тесты Преподавателей ---\n");
    RUN_TEST(TeacherInit);
    RUN_TEST(TeacherAddSingle);
    RUN_TEST(TeacherRemoveBasic);
    
    printf("\n--- Тесты Функций (funcs.c) ---\n");
    RUN_TEST(FuncPrefixStudent);
    RUN_TEST(FuncPrefixNullSafety);
    RUN_TEST(FuncMapStudents);
    RUN_TEST(FuncMapNullSafety);
    RUN_TEST(FuncMapEmptyArray);
    RUN_TEST(FuncFindStudentByID);
    RUN_TEST(FuncFindTeacherByID);
    RUN_TEST(FuncConcatPrint);
    
    printf("\n--- Тесты Памяти ---\n");
    RUN_TEST(MemoryDoubleFreeStudent);
    RUN_TEST(MemoryDoubleFreeTeacher);
    
    TEST_REPORT();
}