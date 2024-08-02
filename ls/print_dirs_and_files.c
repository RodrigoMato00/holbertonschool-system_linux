#include "ls.h"

/**
 * print_dirs_and_files - print directories and files
 * @dirs: array of directory arguments
 * @files: array of file arguments
 * @dir_count: number of directories
 * @file_count: number of files
 */
void print_dirs_and_files(char **dirs, char **files,
	int dir_count, int file_count)
{
	int count;
	int printed = 0;

	for (count = 0; count < dir_count; count++)
	{
		if (printed)
		{
			printf("\n");
		}
		printf("%s:\n", dirs[count]);
		list_directory(dirs[count]);
		printed = 1;
	}
	for (count = 0; count < file_count; count++)
	{
		if (printed)
		{
			printf("\n");
		}
		printf("%s:\n", files[count]);
		list_directory(files[count]);
		printed = 1;
	}
}
