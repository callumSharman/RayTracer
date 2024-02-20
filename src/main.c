#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "camera.h"
#include "materials.h"
#include "utils.h"

#define PI 3.1415926535897932385

int main() {
    spheres_t sphere_list = spheres_init();

    material_t ground_mat = lamb_surface_init(vec3_init(0.5,0.1,0.9));
    sphere_list.spheres[0] = sphere_init(vec3_init(0,-1000,0), 1000, ground_mat);

    int list_idx = 1;

    for(int i = -6; i < 6; i ++){
        for(int j = -9; j < 9; j ++){
            double choose_mat = rand_double();
            point3_t center = vec3_init(i + 0.9*rand_double(), 0.2, j + 0.9*rand_double());

            if(vec3_mag(vec3_sub(center, vec3_init(4,0.2,0))) > 0.9){
                if(choose_mat < 0.6){
                    //lamb
                    vec3_t albedo = vec3_element_wise_multi(vec3_random(),vec3_random());
                    material_t mat = lamb_surface_init(albedo);
                    sphere_list.spheres[list_idx] = sphere_init(center, rand_double_min_max(0.15,0.25), mat);
                    list_idx ++;

                } else if(choose_mat < 0.85){
                    // metal
                    vec3_t albedo = vec3_random_min_max(0.5,1);
                    double fuzz = rand_double_min_max(0,0.5);
                    material_t mat = metal_surface_init(albedo, fuzz);
                    sphere_list.spheres[list_idx] = sphere_init(center, rand_double_min_max(0.15,0.25), mat);
                    list_idx ++;
                } else{
                    // glass
                    material_t mat = dielectric_surface_init(1.5);
                    sphere_list.spheres[list_idx] = sphere_init(center, rand_double_min_max(0.15,0.25), mat);
                    list_idx ++;
                }
            }
        }
    }

    material_t mat1 = dielectric_surface_init(1.5);
    material_t mat2 = metal_surface_init(vec3_init(0.5,0.5,0.5), 0);

    sphere_list.spheres[list_idx] = sphere_init(vec3_init(0.0,1,1), 1.0, mat2);
    list_idx ++;

    sphere_list.spheres[list_idx] = sphere_init(vec3_init(0.0,1,-1), 1.0, mat1);
    list_idx ++;
    sphere_list.spheres[list_idx] = sphere_init(vec3_init(0.0,1,-1), -0.8, mat1);
    list_idx ++;

    // material_t mat2 = lamb_surface_init(vec3_init(0.4,0.2,0.1));
    // sphere_list.spheres[list_idx] = sphere_init(vec3_init(-4,1,0), 1.0, mat2);
    // list_idx ++;

    // material_t mat3 = metal_surface_init(vec3_init(0.7,0.6,0.5), 0.0);
    // sphere_list.spheres[list_idx] = sphere_init(vec3_init(4,1,0), 1.0, mat3);
    // list_idx ++;

    sphere_list.num_spheres = list_idx;

    FILE *img = fopen("image.ppm", "w");

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 200;
    
    camera_t camera = camera_init(aspect_ratio, image_width);

    render(img, camera, sphere_list);

    fclose(img);
    return 0;
}