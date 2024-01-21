#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "vec3.h"
#include "ray.h"

const double ASPECT_RATIO = 16.0 / 9.0;
const int IMG_WIDTH = 400;
const int VIEWPORT_HEIGHT = 2.0;


int main() {

    /*
    1. Calculate the ray from the “eye” through the pixel,
    2. Determine which objects the ray intersects, and
    3. Compute a color for the closest intersection point.
    */

    // set the image height and viewport width, as they can vary with change to the constants
    int img_height = (IMG_WIDTH / ASPECT_RATIO);
    img_height = (img_height < 1) ? 1 : img_height; // must be at least 1 pixel tall
    double viewport_width = VIEWPORT_HEIGHT * (double)((IMG_WIDTH)/img_height);

    // image
    FILE *img = fopen("image.ppm", "w");

    // render
    fprintf(img, "P3\n%d %d\n255\n", IMG_WIDTH, img_height);
    for(int i = 0; i < img_height; i ++) {
        for (int j = 0; j < IMG_WIDTH; ++j) {

            colour_t pixel_colour;
            vec3_init(&pixel_colour, (double)i/(IMG_WIDTH-1), (double)j/(img_height-1), 0);
            write_colour(img, pixel_colour);

        }

        printProgress(i, img_height);
    }


    fclose(img);
    return 0;
}