#include "ls.h"

/**
 * is_directory - check if a path is a directory
 * @path: the path to check
 * Return: 1 if it's a directory, 0 otherwise
 */
int is_directory(const char *path)
{
	struct stat sb;

	if (lstat(path, &sb) == -1)
	{
		if (errno == ENOENT)
		{
			fprintf(stderr, "%s: cannot access %s: No such file or directory\n",
				"hls", path);
		}
		else
		{
			perror("lstat");
		}
		return (-1);
	}

	return (S_ISDIR(sb.st_mode));
}
