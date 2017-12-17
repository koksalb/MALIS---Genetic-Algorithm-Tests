/*****************************************************************************/
/*
* Exercise 1: implement and test genetic operators
*
* MALIS Lab Session
*
/*****************************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "chromosome.h"

int n_cities;

/* the following function is not used in this exercise */
double tsp_round_trip_length(int cities[]) { return 0.; }

/* return a random number within the closed interval [low,high] */
int random_number(int low,int high){
	assert(high>=low);
	return low + (rand() % (high-low+1));
}

/*****************************************************************************/
int main(int argc,char ** argv){
	srand(time(NULL));
	FILE *out;
	int i;
	Chromosome c;
	Chromosome c1;
	Chromosome c2;
	char filename[] = "exercise1.txt";

	n_cities = 100;

	if(fopen_s(&out,filename,"w") != 0) {
		printf("* Error opening file %s\n",filename);
		getchar(); exit(1);
	}

	
	
	for(i=0; i<4; i++) {
		printf("Mutation test %d:\n",i);
		fprintf(out,"Mutation test %d:\n",i);
		chromosome_random(&c);
		chromosome_print(&c);
		chromosome_print_file(out,&c);

		chromosome_mutation(&c);
		chromosome_print(&c);
		chromosome_print_file(out,&c);
	}
	


	
	
	for(i=0; i<4; i++) {
		printf("Crossover test %d:\n",i);
		fprintf(out,"Crossover test %d:\n",i);
		chromosome_random(&c1);
		chromosome_print(&c1);
		chromosome_print_file(out,&c1);
		chromosome_random(&c2);
		chromosome_print(&c2);
		chromosome_print_file(out,&c2);

		chromosome_crossover(&c1,&c2,&c);
		chromosome_print(&c);
		chromosome_print_file(out,&c);
	}
	
	

	fclose(out);

	printf("Finished. Press the Enter key to exit...\n");
	getchar(); // display result until the user press a key
	return 0;
}

