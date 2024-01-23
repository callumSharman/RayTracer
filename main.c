#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "vec3.h"
#include "ray.h"

const double ASPECT_RATIO = 16.0 / 9.0;
const int IMG_WIDTH = 400;
const int VIEWPORT_HEIGHT = 2.0;
const double FOCAL_LENGTH = 1.0;


int main() {

    /*
    1. Calculate the ray from the “eye” through the pixel,
    2. Determine which objects the ray intersects, and
    3. Compute a color for the closest intersection point.
    */
    // // set the image height and viewport width, as they can vary with change to the constants
    // int img_height = (IMG_WIDTH / ASPECT_RATIO);
    // img_height = (img_height < 1) ? 1 : img_height; // must be at least 1 pixel tall
    // double viewport_width = VIEWPORT_HEIGHT * (double)((IMG_WIDTH)/img_height);

    // point3_t camera_center; vec3_init(&camera_center, 0,0,0);

    // // Calculate the vectors across the horizontal and down the vertical viewport edges.
    // vec3_t viewport_u; vec3_init(&viewport_u, viewport_width, 0, 0);
    // vec3_t viewport_v; vec3_init(&viewport_v, 0, -VIEWPORT_HEIGHT, 0);

    // // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    // vec3_t pixel_delta_u; vec3_divide(&pixel_delta_u, IMG_WIDTH, &pixel_delta_u);
    // vec3_t pixel_delta_v; vec3_divide(&pixel_delta_v, img_height, &pixel_delta_v);

    // // Calculate the location of the upper left pixel.
    // /* viewport_upper_left = camera_center 
    //                             - vec3(0, 0, focal_length)  temp_vec1
    //                             - viewport_u/2              temp_vec2
    //                             - viewport_v/2              temp_vec3 */
    // vec3_t viewport_upper_left; 
    // vec3_t temp_vec1; vec3_init(&temp_vec1, 0,0,-1 * FOCAL_LENGTH);
    // vec3_t temp_vec2; vec3_divide(&viewport_u, 2, &temp_vec2); vec3_multiply(&temp_vec2, -1, &temp_vec2);
    // vec3_t temp_vec3; vec3_divide(&viewport_v, 2, &temp_vec3); vec3_multiply(&temp_vec3, -1, &temp_vec3);
    // vec3_add(&camera_center, &temp_vec1, &viewport_upper_left);
    // vec3_add(&viewport_upper_left, &temp_vec2, &viewport_upper_left);
    // vec3_add(&viewport_upper_left, &temp_vec3, &viewport_upper_left); // yikes this is such a bad way to do this
    // /* pixel00_loc = (viewport_upper_left + 0.5) 
    //                         * (pixel_delta_u + pixel_delta_v) */

    // // image
    // FILE *img = fopen("image.ppm", "w");

    // // render
    // fprintf(img, "P3\n%d %d\n255\n", IMG_WIDTH, img_height);
    // for(int i = 0; i < img_height; i ++) {
    //     for (int j = 0; j < IMG_WIDTH; ++j) {

    //         colour_t pixel_colour;
    //         vec3_init(&pixel_colour, (double)i/(IMG_WIDTH-1), (double)j/(img_height-1), 0);
    //         write_colour(img, pixel_colour);

    //     }

    //     printProgress(i, img_height);
    // }


    // fclose(img);
    return 0;
}