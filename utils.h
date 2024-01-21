#ifndef _UTILS_H_
#define _UTILS_H_

#include "vec3.h"

/* Prints a progress bar to the console. Put within a loop, 
   give the current progress and the total (how much progress 
   should be when finished) */
void printProgress(int progress, int total);

/* writes the translated [0, 255] value a single pixel's 
   color to the given file */
void write_colour(FILE *file, colour_t colour);

#endif