#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point for the readelf program.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings representing the command-line arguments.
 *
 * Return: 0 on success, or a non-zero error code on failure.
 */
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    execlp("readelf", "readelf", "-W", "-S", argv[1], (char *)NULL);
    perror("execlp");
    return EXIT_FAILURE;
}
