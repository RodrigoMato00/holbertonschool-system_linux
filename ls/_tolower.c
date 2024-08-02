#include "ls.h"

/**
 * _tolower - converts a character to lowercase if it is uppercase
 * @c: the character to convert
 * Return: the lowercase character,
 * or the original character if it is not uppercase
 */
char _tolower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}
