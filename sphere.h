#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vec3.h"
#include "ray.h"
#include "interval.h"
#include "materials.h"

typedef struct sphere sphere_t;
typedef struct spheres spheres_t;
typedef struct hit_record hit_record_t;

typedef struct material material_t;

struct sphere {
   point3_t center;
   double radius;
   material_t material; // can be of type "metal" or "lamb"
};

struct spheres { // currently holds a max of 10 spheres for simplification
    sphere_t spheres[10];
    int num_spheres;
};

struct hit_record {
   point3_t p; // where did it hit in space?   
   vec3_t normal; // normal to the surface 
   double t; // distance on the ray
   int front_face; // positive when it is the front face
   material_t material; // can be of type "metal" or "lamb"
};

/* initialise sphere instance. Takes the center and radius*/
sphere_t sphere_init(point3_t center, double radius, material_t material);

/* initialise sphere list instance */
spheres_t spheres_init();

/* returns whether a particular ray hits the given sphere, within the given t values
   modifies the given hit record */
int sphere_hit(ray_t r, sphere_t sphere, interval_t rayt, hit_record_t* hr);

/* returns whether a particular ray hits any of the given spheres, within the given t values
   modifies the given hit record */
int spheres_hit(ray_t r, spheres_t sphere_list, interval_t rayt, hit_record_t* hr);

/* copies the information from hr2 to hr1 */
void copy_hit_record(hit_record_t* hr1, hit_record_t* hr2);

/* takes the outward normal of the circle, the ray and the hit_record
   corrects the normal and front_face values */
void sphere_set_face_normal(ray_t r, vec3_t* outward_normal, hit_record_t* hr);

/* prints the sphere to console in easily readable format */
void sphere_print(sphere_t s);

#endif