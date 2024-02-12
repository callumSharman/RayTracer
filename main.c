#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include "materials.h"

int main() {
    material_t ground_mat = lamb_surface_init(vec3_init(0.8,0.8,0.0));
    material_t center_mat = lamb_surface_init(vec3_init(0.7,0.3,0.3));
    material_t left_mat = metal_surface_init(vec3_init(0.8,0.8,0.8));
    material_t right_mat = metal_surface_init(vec3_init(0.8,0.6,0.2));



    spheres_t sphere_list = spheres_init();

    // GROUND SPHERE
    sphere_list.spheres[0] = sphere_init(vec3_init(0,-100.5,-1), 100, ground_mat);

    // CENTER SPHERE
    sphere_list.spheres[1] = sphere_init(vec3_init(0.0,0.0,-1), 0.5, center_mat);

    // LEFT SPHERE
    sphere_list.spheres[2] = sphere_init(vec3_init(-1.0,0.0,-1), 0.5, left_mat);

    // RIGHT SPHERE
    sphere_list.spheres[3] = sphere_init(vec3_init(1.0,0.0,-1), 0.5, right_mat);

    sphere_list.num_spheres = 4;

    FILE *img = fopen("image.ppm", "w");

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    camera_t camera = camera_init(aspect_ratio, image_width);

    render(img, camera, sphere_list);

    fclose(img);
    return 0;
}