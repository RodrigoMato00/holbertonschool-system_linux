#include "ls.h"

/**
 * list_directory - list the contents of the current directory
 * @path: the path to the directory
 */
void list_directory(const char *path)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(path);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			printf("%s  ", entry->d_name);
		}
	}
	printf("\n");

	closedir(dir);
}
