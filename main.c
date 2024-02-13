#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "camera.h"
#include "materials.h"

#define PI 3.1415926535897932385

int main() {
    material_t ground_mat = lamb_surface_init(vec3_init(0.8,0.8,0.0));
    material_t left_mat = lamb_surface_init(vec3_init(0.0,0.0,1.0));
    material_t right_mat = lamb_surface_init(vec3_init(1.0,0.0,0.0));

    spheres_t sphere_list = spheres_init();

    double R = cos(PI/4);

    //sphere_list.spheres[0] = sphere_init(vec3_init(0.0,-100.5,-1), 100, ground_mat);
    sphere_list.spheres[0] = sphere_init(vec3_init(-R,0.0,-1), R, left_mat);
    sphere_list.spheres[1] = sphere_init(vec3_init(R,0.0,-1), R, right_mat);

    sphere_list.num_spheres = 2;

    FILE *img = fopen("image.ppm", "w");

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    camera_t camera = camera_init(aspect_ratio, image_width);

    render(img, camera, sphere_list);

    fclose(img);
    return 0;
}