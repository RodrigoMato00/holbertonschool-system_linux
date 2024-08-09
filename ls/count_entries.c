#include "ls.h"
#include <errno.h>

/**
 * handle_entry - handles resizing and copying entries
 * @entries: double pointer to the array of entries
 * @count: pointer to the count of current entries
 * @size: pointer to the current size of the entries array
 * @entry: the current directory entry to be added
 * Return: updated array of entries or NULL on failure
 */
struct dirent **handle_entry(struct dirent ***entries,
				int *count, int *size, struct dirent *entry)
{
	struct dirent **new_entries;
	int i = 0;

	if (*count >= *size)
	{
		*size *= 2;
		new_entries = malloc(*size * sizeof(struct dirent *));

		if (new_entries == NULL)
		{
			perror("malloc");
			for (; i < *count; i++)
			{
				free((*entries)[i]);
			}
			free(*entries);
			return (NULL);
		}
		for (int i = 0; i < *count; i++)
			new_entries[i] = (*entries)[i];

		free(*entries);
		*entries = new_entries;
	}
	(*entries)[*count] = malloc(sizeof(struct dirent));
	if ((*entries)[*count] == NULL)
	{
		perror("malloc");
		for (int i = 0; i < *count; i++)
		{
			free((*entries)[i]);
		}
		free(*entries);
		return (NULL);
	}
	*(*entries)[*count] = *entry;
	(*count)++;

	return (*entries);
}

/**
 * count_entries - count the number of entries in a directory
 * @path: the path to the directory
 * @num_entries: pointer to store the number of entries
 * Return: array of entries
 */
struct dirent **count_entries(const char *path, int *num_entries)
{
	DIR *dir;
	struct dirent *entry = NULL, **entries;
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
			entries = handle_entry(&entries, &count, &size, entry);
			if (entries == NULL)
			{
				closedir(dir);
				return (NULL);
			}
		}
	}

	*num_entries = count;
	closedir(dir);
	return (entries);
}
