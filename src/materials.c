#include <stdio.h>
#include <math.h>
#include "materials.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "utils.h"

/* initialise a lambertian surface instance */
material_t lamb_surface_init(vec3_t albedo){
    material_t lamb_surface;
    lamb_surface.albedo = albedo;
    lamb_surface.scatter_func = lamb_scatter;
    lamb_surface.fuzz = 0;
    lamb_surface.ir = 0;
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
material_t metal_surface_init(vec3_t albedo, double fuzz){
    material_t metal_surface;
    metal_surface.albedo = albedo;
    metal_surface.scatter_func = metal_scatter;
    fuzz = fuzz < 1 ? fuzz : 1; // make sure fuzz doesnt go over 1
    metal_surface.fuzz = fuzz;
    metal_surface.ir = 0;
    return metal_surface;
}

/* scatters light for a metal surface. Modifies the given hit record, 
   attenuation and scattered ray */
int metal_scatter(ray_t r, hit_record_t* hr, vec3_t* attenuation, 
                                ray_t* scattered){
    
    vec3_t reflected = vec3_reflect(vec3_unit_vec(r.dir), hr->normal);
    scattered->dir = vec3_add(reflected, vec3_multi(vec3_rand_unit(), hr->material.fuzz));
    scattered->orig = hr->p;
    *attenuation = hr->material.albedo;
    return(vec3_dot(scattered->dir, hr->normal) > 0);
}


/* initialise a dielectric surface instance */
material_t dielectric_surface_init(double ir){
    material_t diel_surface;
    diel_surface.albedo = vec3_init(1.0,1.0,1.0);
    diel_surface.scatter_func = dielectric_scatter;
    diel_surface.fuzz = 0;
    diel_surface.ir = ir;
    return diel_surface;
}

/* scatters light for a dielectric surface. Modifies the given hit record, 
   attenuation and scattered ray */
int dielectric_scatter(ray_t r, hit_record_t* hr, vec3_t* attenuation, 
                                ray_t* scattered){
    
    *attenuation = vec3_init(1.0,1.0,1.0);

    double refraction_ratio = hr->front_face ? (1.0/hr->material.ir) : hr->material.ir;

    vec3_t unit_dir = vec3_unit_vec(r.dir);
    double cos_theta = fmin(vec3_dot(vec3_multi(unit_dir,-1), hr->normal), 1.0);
    double sin_theta = sqrt(1.0 - (cos_theta*cos_theta));

    int cannot_refract = (refraction_ratio * sin_theta) > 1.0;
    vec3_t direction;

    if(cannot_refract || reflectance(cos_theta, refraction_ratio) > rand_double()){
        direction = vec3_reflect(unit_dir, hr->normal);
    } else {
        direction = vec3_refract(unit_dir, hr->normal, refraction_ratio);
    }

    scattered->orig = hr->p;
    scattered->dir = direction;

    return 1;
}

/* uses schlick approximation for reflectance */
double reflectance(double cosine, double ref_idx){
    double r0 = (1-ref_idx)/(1+ref_idx);
    r0 = r0*r0;
    return (r0 + (1-r0)*pow((1-cosine), 5));
}

/* copies the information from mat2 to mat1 */
void copy_material(material_t* mat1, material_t* mat2){
    mat1->albedo = mat2->albedo;
    mat1->scatter_func = mat2->scatter_func;
    mat1->fuzz = mat2->fuzz;
    mat1->ir = mat2->ir;
}