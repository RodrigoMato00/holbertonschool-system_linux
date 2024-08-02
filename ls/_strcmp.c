#include "ls.h"

/**
 * _strcmp - compares two strings
 * @str1: the first string to compare
 * @str2: the second string to compare
 * Return: the difference between the first differing characters
 */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 && (_tolower((unsigned char)*str1) ==
			_tolower((unsigned char)*str2)))
	{
		str1++;
		str2++;
	}

	return (_tolower((unsigned char)*str1) - _tolower((unsigned char)*str2));
}
