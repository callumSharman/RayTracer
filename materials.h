#ifndef _MATERIALS_H_
#define _MATERIALS_H_

#include "vec3.h"
#include "ray.h"

typedef struct material material_t;

typedef struct hit_record hit_record_t;

typedef int (*scatter_function)(ray_t, hit_record_t*, 
                vec3_t*, ray_t*);

struct material{
    vec3_t albedo;
    scatter_function scatter_func; // pointer to function used to scatter light
};

/* initialise a lambertian surface instance */
material_t lamb_surface_init(vec3_t albedo);

/* scatters light for a lambertian surface. Modifies the given hit record, 
   attenuation and scattered ray */
int lamb_scatter(ray_t r, hit_record_t* hr, vec3_t* attenuation, 
                                ray_t* scattered);

/* initialise a metal surface instance */
material_t metal_surface_init(vec3_t albedo);

/* scatters light for a metal surface. Modifies the given hit record, 
   attenuation and scattered ray */
int metal_scatter(ray_t r, hit_record_t* hr, vec3_t* attenuation, 
                                ray_t* scattered);

/* copies the information from mat2 to mat1 */
void copy_material(material_t* mat1, material_t* mat2);

#endif