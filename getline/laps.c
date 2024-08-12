#include "laps.h"

/**
 * add_car - Adds a new car to the linked list
 * @head: The head of the list
 * @id: The ID of the new car
 */
void add_car(car_t **head, int id)
{
	car_t *new_car = malloc(sizeof(car_t));
	if (!new_car)
		return;
	new_car->id = id;
	new_car->laps = 0;
	new_car->next = *head;
	*head = new_car;
	printf("Car %d joined the race\n", id);
}

/**
 * find_car - Finds a car in the list
 * @head: The head of the list
 * @id: The ID of the car to find
 * Return: Pointer to the found car, or NULL if not found
 */
car_t *find_car(car_t *head, int id)
{
	while (head)
	{
		if (head->id == id)
			return head;
		head = head->next;
	}
	return NULL;
}

/**
 * race_state - Updates and prints the race state
 * @id: Array of car IDs
 * @size: Number of elements in the array
 */
void race_state(int *id, size_t size)
{
	static car_t *head = NULL;
	if (size == 0)
	{
		while (head)
		{
			car_t *temp = head;
			head = head->next;
			free(temp);
		}
		return;
	}

	for (size_t i = 0; i < size; i++)
	{
		car_t *car = find_car(head, id[i]);
		if (!car)
		{
			add_car(&head, id[i]);
		}
		else
		{
			car->laps++;
		}
	}

	printf("Race state:\n");
	for (car_t *current = head; current; current = current->next)
	{
		printf("Car %d [%d laps]\n", current->id, current->laps);
	}
}
