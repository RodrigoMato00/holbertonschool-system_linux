# Variables para 0-hreadelf
TARGET0 = 0-hreadelf
SRC0    = 0-hreadelf.c
OBJ0    = $(SRC0:.c=.o)

# Variables para 1-hreadelf
TARGET1 = 1-hreadelf
SRC1    = 1-hreadelf.c
OBJ1    = $(SRC1:.c=.o)

CC      = gcc
CFLAGS  = -Wall -Werror -Wextra -pedantic -std=gnu89 -g

.PHONY: all clean fclean re

all: $(TARGET0) $(TARGET1)

$(TARGET0): $(OBJ0)
	$(CC) $(CFLAGS) -o $(TARGET0) $(OBJ0)

$(TARGET1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(OBJ1)

clean:
	rm -f $(OBJ0) $(OBJ1)

fclean: clean
	rm -f $(TARGET0) $(TARGET1)

re: fclean all
