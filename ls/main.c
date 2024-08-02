#include "ls.h"

/**
 * main - entry point
 * @argc: the number of arguments
 * @argv: the arguments
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int count;

	if (argc == 1)
	{
		list_directory(".");
	}
	else
	{
		for (count = 1; count < argc; count++)
		{
			list_directory(argv[count]);
			if (count < argc - 1)
			{
				printf("\n");
			}
		}
	}
	return (0);
}
