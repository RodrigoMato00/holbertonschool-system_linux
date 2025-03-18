#include "elf_parser.h"

/**
 * main - Entry point for the hnm program
 * @argc: The number of command-line arguments
 * @argv: An array of command-line arguments
 *
 * Description: This program takes one or more object files as arguments
 * and processes each file using the parse_elf function. If no arguments
 * are provided, it prints a usage message and exits with a failure status.
 *
 * Return: EXIT_SUCCESS on successful execution, EXIT_FAILURE otherwise
 */
int main(int argc, char **argv)
{

	if (argc < 2)
	{
		fprintf(stderr, "Usage: hnm [objfile ...]\n");
		return (EXIT_FAILURE);
	}

	for (int i = 1; i < argc; i++)
	{
		parse_elf(argv[i]);
	}

	return (EXIT_SUCCESS);
}
