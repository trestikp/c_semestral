/*
 * Transmitter Frequency Collision solver
 *
 * Header for structers - structers.h
 *
 * For function descriptions see structures.c
 */

#include "structures.h"

#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

 /*****************************************************************************
 *                                                                            *
 * Function Prototypes							      *
 *                                                                            *
 *****************************************************************************/ 

int find_neighbors(transmitter *head, int radius);
int assign_frequencies(transmitter *trans_head, frequency *freq_head);
void free_transmitters(transmitter *head);
void free_frequencies(frequency *head);
void print_result(transmitter *head);

#endif
