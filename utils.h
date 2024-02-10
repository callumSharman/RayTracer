#ifndef _UTILS_H_
#define _UTILS_H_

#include "vec3.h"
#include "ray.h"


#define PI 3.1415926535897932385

/* Prints a progress bar to the console. Put within a loop, 
   give the current progress and the total (how much progress 
   should be when finished) */
void printProgress(int progress, int total);

/* writes the translated [0, 255] value a single pixel's 
   color to the given file */
void write_colour(FILE *file, colour_t colour, int samples_per_pixel);

/* self explanatory */
double degrees_to_radians(double degrees);

/* returns a random double in [0,1) */
double rand_double();

/* returns a random double in [min,max) */
double rand_double_min_max(double min, double max);

#endif