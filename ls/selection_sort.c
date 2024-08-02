#include "ls.h"

/**
 * selection_sort - sorts an array of strings
 * @arr: the array of strings to sort
 * @n: the number of elements in the array
 */
void selection_sort(char **arr, int n)
{
	int i, j, min_idx;
	char *temp;

	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (_strcmp(&arr[j], &arr[min_idx]) < 0)
			{
				min_idx = j;
			}
		}
		temp = arr[min_idx];
		arr[min_idx] = arr[i];
		arr[i] = temp;
	}

}
