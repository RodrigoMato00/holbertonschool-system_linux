CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic

hnm: hnm.o elf_parser.o
	$(CC) $(CFLAGS) -o hnm hnm.o elf_parser.o

hnm.o: hnm.c elf_parser.h
	$(CC) $(CFLAGS) -c hnm.c

elf_parser.o: elf_parser.c elf_parser.h
	$(CC) $(CFLAGS) -c elf_parser.c

clean:
	rm -f *.o hnm
