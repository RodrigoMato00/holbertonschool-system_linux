#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - read ELF file with exeve
 * @argc: The number of command line arguments
 * @argv: An array containing the program command line arguments
 * @env:  An array containing the program environment
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char **argv, char **env)
{
	char *cmnd[] = {"/usr/bin/readelf", "-W", "-h", "", NULL};

	(void)argc;
	cmnd[3] = argv[1];
	if (execve("/usr/bin/readelf", cmnd, env) == -1)
	{
		perror("execv");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
