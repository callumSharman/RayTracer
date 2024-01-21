#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "vec3.h"

int main() {
    /*
    vec3_t v;
    vec3_init(&v, 1,2,3);

    vec3_print(&v);
    printf("magnitude of v is %f\n", vec3_mag(&v));


    vec3_t v3;
    vec3_add(&v,&v,&v3);
    printf("v+v = ");
    vec3_print(&v3);
    printf("\n");
    */


    
    // image
    FILE *img = fopen("image.ppm", "w");
    int img_width = 256;
    int img_height = 256;

    // render
    fprintf(img, "P3\n%d %d\n255\n", img_width, img_height);
    for(int i = 0; i < img_height; i ++) {
        for (int j = 0; j < img_width; ++j) {

            colour_t pixel_colour;
            vec3_init(&pixel_colour, (double)i/(img_width-1), (double)j/(img_height-1), 0);
            write_colour(img, pixel_colour);

        }

        printProgress(i, img_height);
    }


    fclose(img);
    return 0;
}