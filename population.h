/*****************************************************************************/
/*
* Some utility routines
*
* MALIS Lab Session
*
/*****************************************************************************/

#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "chromosome.h"

/* There are only resources for a limited population */
#define MAX_POP_SIZE 1000

typedef struct {
  Chromosome chromosome[MAX_POP_SIZE];
  int current_size; /* this should never exceed MAX_POP_SIZE */
} Population;

/* sort population according to fitness: fittest first (shortest round-trip) */
void population_sort(Population * pop);

/* Initialize population to full extend with random chromosomes. */
void population_random(Population *pop,int size);

/* Select the best chromosomes of the population 
 how_much should be a number in the interval (0,1) */
void population_selection(Population * pop, int n_best);

void population_print(Population * pop);

void population_mutation(Population * pop, double mutation_rate);

void population_crossover(Population * pop, int new_size);

#endif
