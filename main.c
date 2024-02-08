#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"

#define ASPECT_RATIO 16.0 / 9.0
#define IMG_WIDTH 400
#define VIEWPORT_HEIGHT 2.0
#define FOCAL_LENGTH 1.0


int main() {

    // set the image height and viewport width, as they can vary with change to the constants
    int img_height = (IMG_WIDTH / (double) (ASPECT_RATIO));
    img_height = (img_height < 1) ? 1 : img_height; // must be at least 1 pixel tall
    double viewport_width = VIEWPORT_HEIGHT * (IMG_WIDTH/(double)img_height);

    point3_t camera_center = vec3_init(0,0,0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3_t viewport_u = vec3_init(viewport_width, 0, 0);
    vec3_t viewport_v = vec3_init(0, -VIEWPORT_HEIGHT, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3_t pixel_delta_u = vec3_divide(viewport_u, IMG_WIDTH);
    vec3_t pixel_delta_v = vec3_divide(viewport_v, img_height);

    // Calculate the location of the upper left pixel.
    /* viewport_upper_left = camera_center 
                            - vec3(0, 0, focal_length)
                            - viewport_u/2
                            - viewport_v/2 */
    vec3_t viewport_upper_left = vec3_sub(vec3_sub(vec3_sub(camera_center, 
										vec3_init(0,0,FOCAL_LENGTH)), 
										vec3_divide(viewport_u, 2)),
										vec3_divide(viewport_v, 2));

    /* pixel00_loc = viewport_upper_left + 
							(0.5 * (pixel_delta_u + pixel_delta_v)) */
	// im fairly certain this is the center of the top left pixel
	vec3_t pixel00_loc = vec3_add(viewport_upper_left, 
								vec3_multi(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));
	

    /*========================image========================*/
    FILE *img = fopen("image.ppm", "w");

    /*========================render========================*/

    spheres_t sphere_list;
    sphere_list.spheres[0] = sphere_init(vec3_init(0,0,-1), 0.5);
    sphere_list.spheres[1] = sphere_init(vec3_init(0,-100.5,-1), 100);


    fprintf(img, "P3\n%d %d\n255\n", IMG_WIDTH, img_height);

    for(int i = 0; i < img_height; i ++) {
        for(int j = 0; j < IMG_WIDTH; ++j) {

			// point = p + (delta_u*j) + (delta_v*i)
			point3_t pixel_center = vec3_add(pixel00_loc, 
									vec3_add(vec3_multi(pixel_delta_u, j), 
											 vec3_multi(pixel_delta_v, i)));
			vec3_t ray_direction = vec3_sub(pixel_center, camera_center);

			ray_t ray = ray_init(camera_center, ray_direction);
			colour_t pixel_colour = ray_colour(ray, sphere_list);

            write_colour(img, pixel_colour);

        }

        printProgress(i, img_height);
    }


    fclose(img);
    return 0;
}