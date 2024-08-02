#include "ls.h"

/**
 * _strcmp - compares two strings
 * @a: first string
 * @b: second string
 * Return: comparison result
 */
int _strcmp(const void *a, const void *b)
{
	const char *str1 = *(const char **)a;
	const char *str2 = *(const char **)b;

	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
