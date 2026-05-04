CC = gcc

MAIN_OBJS = main.o student.o teacher.o funcs.o person.o
TEST_LIB_OBJS = student.o teacher.o funcs.o person.o
TEST_OBJ = tests.o

TARGET = laba2sem
TEST_TARGET = test_runner

all: $(TARGET)

$(TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJ) $(TEST_LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	-cmd /c del /Q /F *.o $(TARGET) $(TEST_TARGET) 2>nul
