#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "utils.h"
#include "vec3.h"
#include "ray.h"
#include "interval.h"


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
void write_colour(FILE *file, colour_t colour, int samples_per_pixel){
    double r = colour.x;
    double g = colour.y;
    double b = colour.z;

    double scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    interval_t intensity = interval_init(0.000,0.999);

    int ir = (int)(255.999 * interval_clamp(intensity, r));
    int ig = (int)(255.999 * interval_clamp(intensity, g));
    int ib = (int)(255.999 * interval_clamp(intensity, b));
    fprintf(file, "%d %d %d\n", ir, ig, ib);
}

/* self explanatory */
double degrees_to_radians(double degrees){
    return(degrees * (PI / 180));
}

/* returns a random double in [0,1) */
double rand_double(){
    //srand(time(NULL)); // seed the random number generator
    return(rand()/(RAND_MAX + 1.0));

}

/* returns a random double in [min,max) */
double rand_double_min_max(double min, double max){
    return(min + (max-min)*rand_double());
}
