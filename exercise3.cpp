/*****************************************************************************/
/*
* Exercise 3: population evolution
*			  example of cities in France			
*
* MALIS Lab Session
*
/*****************************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <float.h>

#include "tsp_utils.h"
#include "chromosome.h"
#include "population.h"

int n_cities=0;
City city[MAX_N_CITIES];

FILE *out;
double selection_rate = 0.5;

/*****************************************************************************/
void perform_test(Population &pop, double mutation_rate, int population_size){

	printf("Mutation rate: %2.3f, Population size: %d\n",mutation_rate,population_size);
	fprintf(out,"Mutation rate: %2.3f, Population size: %d\n",mutation_rate,population_size);

	/* Initialize population with random chromosomes: */
	population_random(&pop,population_size);

	double best_fitness = DBL_MAX; // maximum value for double variable
	for(int generation=0; generation<=500; generation++) {

		population_mutation(&pop,mutation_rate);

		population_crossover(&pop,population_size);

		population_selection(&pop, (int)(selection_rate*(double)population_size));
		
		/* the population is now sorted, so that chromosome[0] is the best one */

		/* keep population if fitness has improved */
		double fitness = pop.chromosome[0].fitness;
		if(best_fitness > fitness) {
			best_fitness = fitness;
			tsp_plot_route("..\\..\\data\\france.ppm",pop.chromosome[0].gene,
				tsp_round_trip_length(pop.chromosome[0].gene),
				generation);
			fprintf(out,"Generation: %4d, population size: %d, Round-trip length: %5.3f, best %5.3f\n",
				generation,population_size,tsp_round_trip_length(pop.chromosome[0].gene),best_fitness);

		}
		printf("Generation: %4d, population size: %d, Round-trip length: %5.3f, best %5.3f\n",
			generation,population_size,tsp_round_trip_length(pop.chromosome[0].gene),best_fitness);
	}
}

/*****************************************************************************/
int main(int argc,char ** argv){
	Population pop;
	char filename[] = "exercise3.txt";
	double mutation_rate;
	int population_size;

	/* open a file to print the results during the iterations */
	if(fopen_s(&out,filename,"w") != 0) {
		printf("* Error opening file %s\n",filename);
		getchar(); exit(1);
	}

	/* initialize cities */
	tsp_read_cities("..\\..\\data\\france.txt");
	tsp_init_plots();

	/* BEGIN IMPLEMENTATION */
	/* with a population size of 100, try the values of the mutation rate 0.01, 0.1, 0.5 */
	/* with a mutation rate of 0.1, try the values of the population size 10, 50, 100 and 500 */
	/* Repeat each experiment 3 times with different random initial populations. */
	/* use the predefined perform_test function */
	
	int test_amount = 3;
	
	//First Half
	population_size = 100;
	for (int j = 0; j < 3; j++)
	{
		if (j == 0) { mutation_rate = 0.01; }
		else if(j==1){ mutation_rate = 0.1; }
		else{ mutation_rate = 0.5; }
		for (int i = 0; i < test_amount; i++)
		{
			printf("Started Population size 100 - Mutation rate %.2f - Test %d \n", mutation_rate,i + 1);
			perform_test(pop, mutation_rate, population_size);
			printf("Started Population size 100 - Mutation rate %.2f - Test %d \n", mutation_rate, i + 1);
			printf("Press a button to start the next test\n");
			getchar();
			system("cls");
		}
	}
	
	//Second Half
	mutation_rate = 0.1;
	for (int j = 0; j < 4; j++)
	{
		if (j == 0) { population_size = 10; }
		else if (j == 1) { population_size = 50; }
		else if (j == 2) { population_size = 100; }
		else { population_size = 500; }
		for (int i = 0; i < test_amount; i++)
		{
			printf("Started Population size %d - Mutation rate %.2f - Test %d \n", population_size,mutation_rate, i + 1);
			perform_test(pop, mutation_rate, population_size);
			printf("Started Population size %d - Mutation rate %.2f - Test %d \n", population_size,mutation_rate, i + 1);
			printf("Press a button to start the next test\n");
			getchar();
			system("cls");
		}
	}

	/* END IMPLEMENTATION */
	printf("Finished. Press the Enter key to exit...\n");
	getchar(); // wait until user presses a key
	return 0;
}