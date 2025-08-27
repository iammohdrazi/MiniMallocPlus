CC = gcc
CFLAGS = -Wall -g -Iinclude
OBJ = src/main.o src/mini_malloc.o src/memory_stats.o src/logger.o
TARGET = MiniMallocPlus

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)
