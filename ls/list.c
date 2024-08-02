#include "ls.h"

/**
 * list_directory - list the contents of a directory
 * @path: the path to the directory
 */
void list_directory(const char *path)
{
	DIR *dir;
	struct dirent *entry, **entries;
	int count = 0, num_entries = 0;

	dir = opendir(path);
	if (dir == NULL)
	{
		fprintf(stderr, "%s: cannot access %s: %s\n",
			"hls", path, strerror(errno));
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
			num_entries++;
	}
	rewinddir(dir);
	entries = malloc(num_entries * sizeof(struct dirent *));
	if (entries == NULL)
	{
		perror("malloc");
		closedir(dir);
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			entries[count] = entry;
			count++;
		}
	}
	selection_sort_dirent(entries, num_entries);
	for (count = 0; count < num_entries; count++)
	{
		printf("%s  ", entries[count]->d_name);
	}
	printf("\n");
	free(entries);
	closedir(dir);
}
