#include "ls.h"

/**
 * process_args - process the command-line arguments
 * @argc: the number of arguments
 * @argv: the arguments
 * @dirs: array to store directory arguments
 * @files: array to store file arguments
 * @dir_count: pointer to directory count
 * @file_count: pointer to file count
 */
void process_args(int argc, char *argv[], char **dirs, char **files,
	int *dir_count, int *file_count)
{
	int count;

	for (count = 1; count < argc; count++)
	{
		int dir_status = is_directory(argv[count]);

		if (dir_status == 1)
		{
			dirs[*dir_count] = argv[count];
			(*dir_count)++;
		}
		else if (dir_status == 0)
		{
			files[*file_count] = argv[count];
			(*file_count)++;
		}
	}
}
