/*
 * Transmitter Frequency Collision solver
 *
 * Header for structers - structers.h
 *
 * For function descriptions see structures.c
 */


#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "constants.h"

/*
 *	frequency *add_frequency(frequency *last, int id, int value) {
 *
 * 	Function adds new frequency at the end of a linked list.
 * 	For faster insertion takes last linked list element as 
 * 	parameter. If memory allocation fails prints relevant
 * 	error to the console and returns NULL.
 *
 * 	Returns *frequency that was just added to the linked list.
 */
frequency *add_frequency(frequency *last, int id, int value) {
	frequency *temp = (frequency*) malloc(sizeof(frequency));

	/* check if memory was successfully alloceted */
	if (!temp) {
		printf(ERROR_2);
		return NULL;
	}

	temp->id = id;
	temp->value = value;
	temp->used = 0;
	temp->next = NULL;
	
	/* if this is first element in linked list */
	if (!last) {
		return temp;
	}

	last->next = temp;
	return last->next;
}

/*
 *	transmitter *add_transmitter(transmitter *last, int id,
 *				     float x, float y) {
 *	
 *	Function adds new transmitter at the end of a linked list.
 *	For faster insertion takes last linked list element as
 *	parameter. If memory allocation fails prints relevant
 *	error to the console and return NULL.
 *
 *	Returns *transmitter that was just added to the linked list.
 */
transmitter *add_transmitter(transmitter *last, int id, float x, float y) {
	transmitter *temp = (transmitter*) malloc(sizeof(transmitter));

	/* check if memory was successfully allocated */
	if (!temp) {
		printf(ERROR_2);
		return NULL;
	}
	
	temp->id = id;
	temp->x = x;
	temp->y = y;
	temp->frequency = -1;
	temp->is_in_stack = 0;
	temp->neighbor_head = NULL;
	temp->next = NULL;

	/* if this is first element in linked list */
	if (!last) {
		return temp;
	}

	last->next = temp;
	return last->next;
}

/*
 *	int add_neighbor(transmitter *trans, transmitter *neighbor) {
 *
 * 	Function adds a neighbor of a transmitter.
 * 	Unlike add_frequency and add_transmitter goes through the
 * 	whole linked list to add the neighbor at the end.
 *
 * 	Returns 1 for success, 0 for failure.
 */
int add_neighbor(transmitter *trans, transmitter *neighbor) {
	stack_node *temp = (stack_node*) malloc(sizeof(stack_node));
	stack_node *last = trans->neighbor_head;

	/* check if memory was successfully allocated */
	if (!temp) {
		printf(ERROR_2);
		return 0;
	}
	
	temp->data = neighbor;
	temp->next = NULL;

	/* if this is first neighbor */
	if (!last) {
		trans->neighbor_head = temp;
		return 1;
	}

	while (last->next) {
		last = last->next;
	}

	last->next = temp;

	return 1;
}

/*
 *	int is_empty(stack_node *root) {
 *
 *	Function checks if stack is empty.
 *	Checks stack got from parameter.
 *
 *	Returns 0 if the stack is NOT empty.
 *		1 otherwise.
 */
int is_empty(stack_node *root) {
	return !root;
}

/*
 *	void push(stack_node **root, transmitter *trans) {
 *
 * 	Pushes transmitter to stack.
 *
 * 	Returns 0 if memory allocation failed.
 * 		1 on success.
 */
int push(stack_node **root, transmitter *trans) {
	stack_node *temp = (stack_node*) malloc(sizeof(stack_node));

	if (!temp) {
		printf(ERROR_2);
		return 0;
	}

	temp->data = trans;
	trans->is_in_stack = 1;
	temp->next = *root;
	*root = temp;

	return 1;
}

/*
 *	transmitter *pop(stack_node **root) {
 *
 * 	Pops transmitter from stack
 *
 * 	Returns *transmitter or NULL if stack is empty.
 */
transmitter *pop(stack_node **root) {
	stack_node *temp = *root;
	transmitter *popped;

	if (is_empty(*root)) 
		return NULL;

	*root = (*root)->next;
	popped = temp->data;
	/* following line can be removed, it's just extra precaution */
	popped->is_in_stack = 0;
	free(temp);
		
	return popped;
}
