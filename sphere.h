#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vec3.h"
#include "ray.h"

typedef struct sphere sphere_t;
typedef struct spheres spheres_t;
typedef struct hit_record hit_record_t;

struct sphere {
   point3_t center;
   double radius;
};

struct spheres { // currently holds a max of 10 spheres for simplification
    sphere_t spheres[10];
};

struct hit_record {
   point3_t p; // where did it hit in space?   
   vec3_t normal; // normal to the surface
   double t; // distance on the ray
   int front_face; // positive when it is the front face
};

/* initialise sphere instance. Takes the center and radius*/
sphere_t sphere_init(point3_t center, double radius);

/* returns whether a particular ray hits the given sphere, within the given t values
   modifies the given hit record */
int sphere_hit(ray_t r, sphere_t sphere, double rayt_min, double rayt_max, hit_record_t* hr);

/* returns whether a particular ray hits any of the given spheres, within the given t values
   modifies the given hit record */
int spheres_hit(ray_t r, spheres_t spheres, double rayt_min, double rayt_max, hit_record_t* hr);

/* copies the information from hr2 to hr1 */
void copy_hit_record(hit_record_t* hr1, hit_record_t* hr2);

/* takes the outward normal of the circle, the ray and the hit_record
   corrects the normal and front_face values */
void sphere_set_face_normal(ray_t r, vec3_t* outward_normal, hit_record_t* hr);

#endif