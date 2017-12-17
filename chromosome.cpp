/*****************************************************************************/
/*
* Routines to manipulate chromosomes
*
* MALIS Lab Session
*
/*****************************************************************************/

#include <assert.h>
#include "tsp_utils.h"
#include "chromosome.h"

/*****************************************************************************/
/* Print a chromosome */
void chromosome_print(Chromosome * c){
	int i;

	printf("  Chromosome: fitness=%5.2f, cities:",c->fitness);
	for(i=0; i<n_cities; i++){
		printf(" %3d",c->gene[i]);
	}
	printf("\n");
}

/*****************************************************************************/
/* Print a chromosome in a file */
void chromosome_print_file(FILE *out, Chromosome * c){
	int i;

	fprintf(out,"  Chromosome: fitness=%5.2f, cities:",c->fitness);
	for(i=0; i<n_cities; i++){
		fprintf(out," %3d",c->gene[i]);
	}
	fprintf(out,"\n");
}

/*****************************************************************************/
/* Initialize a chromosome randomly:
- create an ordered sequence
- randomly swap genes many times
*/
void chromosome_random(Chromosome * c){
	int i, i1, i2, g;

	/* create a ordered sequence of cities */ 
	for(i=0; i<n_cities; i++) {
		c->gene[i]=i; 
	}

	/* Now, swap random cities in the sequence */
	for(i=0; i<n_cities*10; i++){
		i1 = random_number(0,n_cities-1);
		i2 = random_number(0,n_cities-1);
		g = c->gene[i1];
		c->gene[i1] = c->gene[i2];
		c->gene[i2] = g;
	}

	c->fitness = chromosome_compute_fitness(c);
}
bool IsItThere(int a, int start, int end, int copied[]);
/*****************************************************************************/
/* Computes the fitness (round-trip length) of a chromosome */
double chromosome_compute_fitness(Chromosome * c){

	c->fitness = tsp_round_trip_length(c->gene);
	return c->fitness;
}

/*****************************************************************************/
/* This routine implements the mutation operator */
void chromosome_mutation(Chromosome * c) {
	/* invert a subsequence of this chromosome */
	int first, last;		/* beginning and end of subsequence */

	/* BEGIN IMPLEMENTATION */
	/* Generate random positions for the beginning and end of the subsequence */
	/* Reverse the chosen subsequence of cities */
	/* END IMPLEMENTATION */

	int i, i1, i2, g;
	first = random_number(0, n_cities - 4);
	last = random_number(first+2, n_cities - 1);
	
	//printf("Mutation Variables: Start: %d End: %d \n",first,last);
	/* Now, swap random cities in the sequence */
	for(i=first; i< first + (last-first)/2; i++){
		i1 = i;
		i2 = last+first-i;
		g = c->gene[i1];
		c->gene[i1] = c->gene[i2];
		c->gene[i2] = g;
	}


	/* always keep fitness updated */
	c->fitness = chromosome_compute_fitness(c);

	//the loop checks if any value is repeated in the array of copied. If so gives assert(true)
	for(int i=0; i<n_cities; i++){

		for(int j = i+1;j<n_cities; j++){
			if(c->gene[i]==c->gene[j])
			{
				assert(true);
			}
										}
	}

	// For debugging: check that each city appears exactly once
#ifdef _DEBUG
	{
		int check[MAX_N_CITIES];
	    int i, city;
	    for(i=0; i<n_cities; i++) { 
		    int city = c->gene[i];
		    assert(city < n_cities);
		    assert(city >= 0);
		    check[city]=1; 
	    }
	    for(city=0;city<n_cities;city++) { 
		    assert(check[city]==1); 
	    }
	}
#endif
}

/*****************************************************************************/
/* This routine implements the crossover operator */
void chromosome_crossover(Chromosome * mother, Chromosome * father, Chromosome * offspring){
	int first, last;			/* beginning and end of mother's subsequence */
	int copied[MAX_N_CITIES]; /* array to remember which genes have been already copied to the offspring */
	int offspring_pos, father_pos;

	/* initialize Offspring does not yet contain any genes. */
	for(int i=0; i<n_cities; i++) copied[i]=0;

	/* BEGIN IMPLEMENTATION */
	/* Generate random positions for the beginning and end of the subsequence */
	/* Copy the mother's sub-sequence to the offspring in the same position */
	/* update the "copied" array to keep track of which cities have been copied to the offspring */
	/* END IMPLEMENTATION */

	int start = random_number(0, n_cities - 2);
	int end = random_number(start+1, n_cities - 1);

	//printf("Crossover Variables: Start: %d End: %d \n",start,end);

	int size = end - start+1;
	
	int pos = 0;
	for (int i = start; i < end; i++)
	{
		
		//offspring->gene[i] = mother->gene[i];
		copied[i]= mother->gene[i];
		offspring->gene[i] = mother->gene[i];
		pos++;
	}
	





	/* Now, fill up the remaining positions of the offspring with the cities
	from the father's chromosome while conserving the ordering */

	father_pos = 0;
	for(offspring_pos = 0 ; offspring_pos < n_cities ; offspring_pos++){
		if (
				/* BEGIN IMPLEMENTATION */
				/* test if offspring_pos is pointing to an empty position in offspring */ 
				/* END IMPLEMENTATION */
			copied[offspring_pos] == 0
			)
		{

			//we are here: offspring_pos


			/* BEGIN IMPLEMENTATION */
			/* offspring_pos is an empty position, fill it with the next gene in the father's chromosome */
			/* update the 'copied' array */
			/* END IMPLEMENTATION */
			

			for (int j = father_pos; j < n_cities; j++)
			{
				if (IsItThere(father->gene[j], start, end, copied))
				{
					
				}
				else
				{
					copied[offspring_pos] = father->gene[j];
					offspring->gene[offspring_pos] = father->gene[j];
					father_pos = j+1;


					break;
				}
					

			}




			/* check that positions remain within allowed range */
			assert(offspring_pos < n_cities && offspring_pos >= 0);
			assert(father_pos <= n_cities && father_pos >= 0);
		}
	}

	/* Sanity check: All the cities should appear exactly once in the
	offspring, otherwise something went wrong in the algorithm */

	//the loop checks if any value is repeated in the array of copied. If so gives assert(true)
	for(int i=0; i<n_cities; i++){

		for(int j = i+1;j<n_cities; j++){
			if(copied[i]==copied[j])
			{
				assert(true);
			}
										}
	}

	/* always keep fitness updated */
	offspring->fitness = chromosome_compute_fitness(offspring);
}


//a function to check if a value is in the array given between start and end points or not. TRUE=yes, FALSE=no
bool IsItThere(int a,int start,int end,int copied[])
{
	for (int i = start; i < end; i++)
	{
		if (a == copied[i]) { return true; }


	}
	return false;
}