#include "ls.h"

/**
 * list_directory - list the contents of the current directory
 */
void list_directory(void)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(".");
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
