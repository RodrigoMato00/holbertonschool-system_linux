#include "ls.h"

/**
 * selection_sort_dirent - sorts an array of dirent structures
 * @arr: the array of dirent structures to sort
 * @n: the number of elements in the array
 */
void selection_sort_dirent(struct dirent **arr, int n)
{
	int i, j, min_idx;
	struct dirent *temp;

	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (compare_dirent(arr[j], arr[min_idx]) < 0)
			{
				min_idx = j;
			}
		}
		temp = arr[min_idx];
		arr[min_idx] = arr[i];
		arr[i] = temp;
	}
}
