#include <stdio.h>
#include "materials.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"

/* initialise a lambertian surface instance */
material_t lamb_surface_init(vec3_t albedo){
    material_t lamb_surface;
    lamb_surface.albedo = albedo;
    lamb_surface.scatter_func = lamb_scatter;
    return lamb_surface;
}

/* scatters light for a lambertian surface. Modifies the given hit record, 
   attenuation and scattered ray */
int lamb_scatter(ray_t r, hit_record_t* hr, vec3_t* attenuation, 
                                ray_t* scattered){
    
    vec3_t scatter_dir = vec3_add(hr->normal, vec3_rand_unit());
    if(near_zero(scatter_dir)) scatter_dir = hr->normal;

    scattered->dir = scatter_dir;
    scattered->orig = hr->p;
    *attenuation = hr->material.albedo;

    return 1;
}


/* initialise a metal surface instance */
material_t metal_surface_init(vec3_t albedo){
    material_t metal_surface;
    metal_surface.albedo = albedo;
    metal_surface.scatter_func = metal_scatter;
    return metal_surface;
}

/* scatters light for a metal surface. Modifies the given hit record, 
   attenuation and scattered ray */
int metal_scatter(ray_t r, hit_record_t* hr, vec3_t* attenuation, 
                                ray_t* scattered){
    vec3_t reflected = vec3_reflect(vec3_unit_vec(r.dir), hr->normal);
    scattered->dir = reflected;
    scattered->orig = hr->p;
    *attenuation = hr->material.albedo;
    return 1;
}

/* copies the information from mat2 to mat1 */
void copy_material(material_t* mat1, material_t* mat2){
    mat1->albedo = mat2->albedo;
    mat1->scatter_func = mat2->scatter_func;
}