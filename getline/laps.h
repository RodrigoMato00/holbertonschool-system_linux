#ifndef LAPS_H
#define LAPS_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * struct car - a struct to store car data
 * @id: the identifier of the car
 * @laps: the number of laps completed by the car
 * @next: pointer to the next car in the list
 */
typedef struct car
{
	int id;
	int laps;
	struct car *next;
} car_t;

void race_state(int *id, size_t size);

#endif /* LAPS_H */
