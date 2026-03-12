CC = gcc
SRCS = main.c student.c teacher.c funcs.c tests.c
OBJS = $(SRCS:.c=.o)
TARGET = laba2sem

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
