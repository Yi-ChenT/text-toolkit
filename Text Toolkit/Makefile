
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = main.exe
SRCS = main.c fileProcessing.c operations.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c fileProcessing.h operations.h
	$(CC) $(CFLAGS) -c $< -o $@

fileProcessing.o: fileProcessing.c fileProcessing.h
	$(CC) $(CFLAGS) -c $< -o $@

operations.o: operations.c operations.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run:
	$(TARGET)
	./$(TARGET)
