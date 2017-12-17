/*****************************************************************************/
/*
* Some utility routines
*
* MALIS Lab Session
*
/*****************************************************************************/

#ifndef TSP_UTILS_H
#define TSP_UTILS_H

typedef struct {
  char name[20];
  int x;
  int y; 
} City;

#define MAX_N_CITIES 100
extern int n_cities;
extern City city[];

int random_number(int low,int high);

void tsp_plot_route(char *filename, int sequence[],double length, int generation);

void tsp_init_plots();

void tsp_read_cities(char *filename);

double tsp_city_distance(int i,int j);

double tsp_round_trip_length(int city_ids[]);
#endif