#include "ls.h"

/**
 * _entries - resize the entries array
 * @entries: the array of entries
 * @size: the new size of the array
 * Return: 1 on success, 0 on failure
 */
int _entries(struct dirent ***entries, int size)
{
	struct dirent **temp = realloc(*entries, size * sizeof(struct dirent *));

	if (temp == NULL)
	{
		perror("realloc");
		return (0);
	}
	*entries = temp;
	return (1);
}
