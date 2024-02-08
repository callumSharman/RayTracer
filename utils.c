#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "vec3.h"
#include "ray.h"


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

/* takes a sphere defined by 'center', and 'radius', along with a ray and 
   returns < 0 if no intersection, otherwise returns t of intersection/s  */
double hit_sphere(point3_t center, double radius, ray_t r){
    // skipped step 6.2 to simplify this code
    // using the quadratic formula find the discriminant to see if intersection
    
    double a = vec3_dot(r.dir, r.dir);
    double b = 2 * vec3_dot(r.dir, vec3_sub(r.orig, center));
    double c = vec3_dot(vec3_sub(r.orig, center), vec3_sub(r.orig, center)) - radius*radius;
    double discriminant = (b*b) - (4*a*c);

    if(discriminant < 0){
        return -1.0;
    } else { // start by assuming only one solution
        return (((-1*b) - sqrt(discriminant))/
                        (2.0*a));
    }
}