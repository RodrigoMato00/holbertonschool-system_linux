#include "ls.h"

/**
 * list_directory - list the contents of a directory
 * @path: the path to the directory
 */
void list_directory(const char *path)
{
	struct dirent **entries;
	int count = 0, num_entries = 0;

	entries = count_entries(path, &num_entries);
	if (entries == NULL)
	{
		return;
	}

	selection_sort_dirent(entries, num_entries);

	for (count = 0; count < num_entries; count++)
	{
		printf("%s  ", entries[count]->d_name);
	}
	printf("\n");
	free_entries(entries, num_entries);
}
