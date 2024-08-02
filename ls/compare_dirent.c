#include "ls.h"

/**
 * compare_dirent - compares two dirent structures by their names
 * @a: first dirent structure
 * @b: second dirent structure
 * Return: the difference between the first differing characters
 */
int compare_dirent(const struct dirent *a, const struct dirent *b)
{
	return (_strcmp(a->d_name, b->d_name));
}
