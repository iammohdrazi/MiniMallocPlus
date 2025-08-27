CC = gcc
CFLAGS = -Wall -g -Iinclude
SRC = src/main.c src/mini_malloc.c src/memory_stats.c src/logger.c
OBJ = $(SRC:.c=.o)
TARGET = MiniMallocPlus

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET) memory_log.txt
