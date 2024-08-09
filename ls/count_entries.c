#include "ls.h"
#include <errno.h>

/**
 * count_entries - count the number of entries in a directory
 * @path: the path to the directory
 * @num_entries: pointer to store the number of entries
 * Return: array of entries
 */
struct dirent **count_entries(const char *path, int *num_entries)
{
	DIR *dir;
	struct dirent *entry, **entries;
	int count = 0, size = 10;

	dir = opendir(path);
	if (dir == NULL)
	{
		fprintf(stderr, "cannot access %s: ", path);
		perror("");

		return (NULL);
	}

	entries = malloc(size * sizeof(struct dirent *));
	if (entries == NULL)
	{
		perror("malloc");
		closedir(dir);
		return (NULL);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			if (count >= size)
			{
				size *= 2;
				if (!_entries(&entries, size))
				{
					free(entries);
					closedir(dir);
					return (NULL);
				}
			}
			entries[count] = entry;
			count++;
		}
	}
	*num_entries = count;
	closedir(dir);
	return (entries);
}
