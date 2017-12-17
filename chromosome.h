/*****************************************************************************/
/*
* Routines to manipulate chromosomes
*
* MALIS Lab Session
*
/*****************************************************************************/

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <stdio.h>
#include "tsp_utils.h"

typedef struct {
  int gene[MAX_N_CITIES];
  double fitness;
} Chromosome;

void chromosome_print(Chromosome * c);

void chromosome_print_file(FILE *out, Chromosome * c);

void chromosome_random(Chromosome * c);

double chromosome_compute_fitness(Chromosome * c);

void chromosome_mutation(Chromosome * c);

void chromosome_crossover(Chromosome * mother, Chromosome * father, Chromosome * offspring);

#endif