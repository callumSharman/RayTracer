#ifndef _UTILS_H_
#define _UTILS_H_

#include "vec3.h"
#include "ray.h"

/* Prints a progress bar to the console. Put within a loop, 
   give the current progress and the total (how much progress 
   should be when finished) */
void printProgress(int progress, int total);

/* writes the translated [0, 255] value a single pixel's 
   color to the given file */
void write_colour(FILE *file, colour_t colour);

/* takes a sphere defined by 'center', and 'radius', along with a ray and 
   returns < 0 if no intersection, otherwise returns t of intersection/s */
double hit_sphere(point3_t center, double radius, ray_t r);

#endif