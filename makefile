CC = gcc
CFLAGS = -Wall
TARGET = main.exe


all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET)


clean:
	rm -f $(TARGET)

.PHONY: all clean