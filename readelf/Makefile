TARGET = 0-hreadelf
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

0-hreadelf: 0-hreadelf.c
	$(CC) $(CFLAGS) 0-hreadelf.c -o $(TARGET)

all: $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean