/*
 * Transmitter Frequency Collision solver
 *
 * Header for structers - structers.h
 *
 * For function descriptions see structures.c
 */

#ifndef _STRUCTURES_H
#define _STRUCTURES_H

/******************************************************************************
 *									      *
 * Structures and Datatypes						      *
 * 									      *
 *****************************************************************************/

typedef struct the_frequency {
	int id;
	int value;
	int used;
	struct the_frequency *next;
} frequency;

struct the_stack_node;

typedef struct the_transmitter {
	int id, frequency;
	float x, y;
	int is_in_stack;
	struct the_stack_node *neighbor_head;
	struct the_transmitter *next;
} transmitter;

typedef struct the_stack_node {
	transmitter *data;
	struct the_stack_node *next;	
} stack_node;

/******************************************************************************
 *									      *
 * Function Prototypes							      *
 * 									      *
 *****************************************************************************/


frequency *add_frequency(frequency *last, int id, int value);
transmitter *add_transmitter(transmitter *last, int id, float x, float y);
int add_neighbor(transmitter *trans, transmitter *neighbor);
int is_empty(stack_node *root);
int push(stack_node **root, transmitter *trans);
transmitter *pop(stack_node **root);

#endif
