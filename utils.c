#include <stdio.h>
#include "utils.h"
#include "vec3.h"


/* Prints a progress bar to the console. Put within a loop, 
   give the current progress and the total (how much progress 
   should be when finished) */
void printProgress(int progress, int total) {
    const int barWidth = 50;
    int filledWidth = barWidth * progress / total;

    printf("[");
    
    for (int i = 0; i < barWidth; ++i) {
        if (i < filledWidth) {
            printf("#");
        } else {
            printf(" ");
        }
    }

    printf("] %d%%\r", progress * 100 / total);
    fflush(stdout);  // Flush the output to ensure immediate update
}

/* writes the translated [0, 255] value a single pixel's 
   color to the given file */
void write_colour(FILE *file, colour_t colour){
    int ir = (int)(255.999 * colour.x);
    int ig = (int)(255.999 * colour.y);
    int ib = (int)(255.999 * colour.z);
    fprintf(file, "%d %d %d\n", ir, ig, ib);
}