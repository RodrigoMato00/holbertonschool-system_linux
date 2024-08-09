#include "ls.h"

/**
 * _entries - resize the entries array
 * @entries: the array of entries
 * @size: the new size of the array
 * Return: 1 on success, 0 on failure
 */
int _entries(struct dirent ***entries, int size)
{
	struct dirent **temp;

	temp = malloc(size * sizeof(struct dirent *));
	if (temp == NULL)
	{
		perror("malloc");
		return (0);
	}

	memcpy(temp, *entries, size / 2 * sizeof(struct dirent *));

	free(*entries);

	*entries = temp;

	return (1);
}
