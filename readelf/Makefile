TARGET = 0-hreadelf
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

SRC = 0-hreadelf.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all
