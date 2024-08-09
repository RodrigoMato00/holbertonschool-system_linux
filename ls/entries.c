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
	int count;

	temp = malloc(size * sizeof(struct dirent *));
	if (temp == NULL)
	{
		perror("malloc");
		return (0);
	}

	for (count = 0; count < size / 2; count++)
	{
		temp[count] = (*entries)[count];
	}
#

	free(*entries);

	*entries = temp;

	return (1);
}
