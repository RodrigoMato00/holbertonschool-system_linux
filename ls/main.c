#include "ls.h"

/**
 * main - entry point
 * @argc: the number of arguments
 * @argv: the arguments
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	char **dirs = malloc(argc * sizeof(char *));
	char **files = malloc(argc * sizeof(char *));
	int dir_count = 0, file_count = 0;

	if (argc == 1)
	{
		list_directory(".");
		free(dirs);
		free(files);
	}
	else
	{
		process_args(argc, argv, dirs, files, &dir_count, &file_count);
		selection_sort(dirs, dir_count);
		selection_sort(files, file_count);
		print_dirs_and_files(dirs, files, dir_count, file_count);
		free(dirs);
		free(files);
	}
	return (0);
}
