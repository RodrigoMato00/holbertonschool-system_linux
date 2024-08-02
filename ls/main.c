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
	int count;

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
		if (argc > 2)
		{
			print_dirs_and_files(dirs, files, dir_count, file_count);
		}
		else
		{
			for (count = 0; count < dir_count; count++)
			{
				list_directory(dirs[count]);
			}
			for (count = 0; count < file_count; count++)
			{
				list_directory(files[count]);
			}
		}
		free(dirs);
		free(files);
	}
	return (0);
}
