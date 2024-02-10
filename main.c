#include <stdio.h>
#include <stdlib.h>
#include "camera.h"

int main() {
    spheres_t sphere_list = spheres_init();
    sphere_list.spheres[0] = sphere_init(vec3_init(0,0,-1), 0.5);
    sphere_list.spheres[1] = sphere_init(vec3_init(0,-100.5,-1), 100);
    sphere_list.num_spheres = 2;

    FILE *img = fopen("image.ppm", "w");

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    camera_t camera = camera_init(aspect_ratio, image_width);

    render(img, camera, sphere_list);

    fclose(img);
    return 0;
}