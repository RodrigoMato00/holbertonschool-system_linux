#include "ls.h"

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
		fprintf(stderr, "%s: cannot access %s: %s\n",
			"hls", path, strerror(errno));

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
				struct dirent **temp = realloc(entries, size * sizeof(struct dirent *));

				if (temp == NULL)
				{
					perror("realloc");
					free(entries);
					closedir(dir);
					return (NULL);
				}
				entries = temp;
			}
			entries[count] = entry;
			count++;
		}
	}
	*num_entries = count;
	closedir(dir);
	return (entries);
}
