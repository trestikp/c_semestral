#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "constants.h"

frequency *add_frequency(frequency *last, int id, int value) {
	frequency *temp = (frequency*) malloc(sizeof(frequency));

	if(!temp) {
		printf(ERROR_2);
		/* Exit code? */
		return NULL;
	}

	temp->id = id;
	temp->value = value;
	temp->used = 0;
	
	if(!last) {
		return temp;
	}

	last->next = temp;
	return last->next;
}

transmitter *add_transmitter(transmitter *last, int id, float x, float y) {
	transmitter *temp = (transmitter*) malloc(sizeof(transmitter));

	if(!temp) {
		printf(ERROR_2);
		return NULL;
	}
	
	temp->id = id;
	temp->x = x;
	temp->y = y;
	temp->frequency = -1;
	temp->is_in_stack = 0;

	if(!last) {
		return temp;
	}

	last->next = temp;
	return last->next;
}

/*
int add_neighbor(transmitter *trans, transmitter *neighbor) {
	stack_node *temp = (stack_node*) malloc(sizeof(stack_node));

	if(!temp) {
		printf(ERROR_2);
		return 0;
	}

	temp->data = neighbor;
	temp->next = trans->neighbor_head;
	trans->neighbor_head = temp;

	return 1;
}
*/

int add_neighbor(transmitter *trans, transmitter *neighbor) {
	stack_node *temp = (stack_node*) malloc(sizeof(stack_node));
	stack_node *last = trans->neighbor_head;

	if(!temp) {
		printf(ERROR_2);
		return 0;
	}
	
	temp->data = neighbor;
	temp->next = NULL;

	if(!last) {
		trans->neighbor_head = temp;
		return 1;
	}

	while(last->next) {
		last = last->next;
	}

	last->next = temp;

	return 1;
}

int is_empty(stack_node *root) {
	return !root;
}

void push(stack_node **root, transmitter *trans) {
	stack_node *temp = (stack_node*) malloc(sizeof(stack_node));

	temp->data = trans;
	trans->is_in_stack = 1;
	temp->next = *root;
	*root = temp;
}

transmitter *pop(stack_node **root) {
	stack_node *temp = *root;
	transmitter *popped;

	if(is_empty(*root)) 
		return NULL;

	*root = (*root)->next;
	popped = temp->data;
	/* following line can be removed, is just extra precaution */
	popped->is_in_stack = 0;
	free(temp);
		
	return popped;
}

void print_freq(frequency *head) {
	while(head) {
		printf("Frequency: %d %d\n", head->id, head->value);
		head = head->next;
	}
}

void print_tran(transmitter *head) {
	while(head) {
		printf("Transmitter: %d %f %f\n", head->id, head->x, head->y);
		head = head->next;
	}
}

void print_neighbors(transmitter *trans) {
	stack_node *hopper = trans->neighbor_head;
	while(hopper) {
		printf("Print neighbor: %d of %d - %d\n", hopper->data->id, trans->id, hopper->data->frequency);
		hopper = hopper->next;
	}
}
