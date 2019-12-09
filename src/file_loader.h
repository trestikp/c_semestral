/* 
 * Transmitter Frequency Collision solver 
 * 
 * Header for structers - structers.h 
 * 
 * For function descriptions see structures.c 
 */

#include "structures.h"

#ifndef _FILE_LOADER_H
#define _FILE_LOADER_H

/******************************************************************************
*                                                                            *
* Function Prototypes                                                        *
*                                                                            *
*****************************************************************************/

int load_file(char *file_name, transmitter **transmitter_head,
	       frequency **frequency_head, int *rad);

#endif
