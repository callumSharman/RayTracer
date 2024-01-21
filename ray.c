#include <stdio.h>
#include "utils.h"
#include "vec3.h"
#include "ray.h"


/* initialise ray instance. Takes origin, direction and pointer to ray */
void ray_init(ray_t* ray, point3_t* origin, vec3_t* direction){
    vec3_copy_into(origin, &(ray->orig)); // sets the origin
    vec3_copy_into(direction, &(ray->dir)); // sets the direction
}


/* finds the point on the given ray at t, puts it into the given point */
void ray_point_at(ray_t* ray, double t, point3_t* result){
    // P(t) = A + tb (A is orign, b is direction)

    point3_t res; 
    vec3_t tb;
    vec3_multiply(&(ray->dir), t, &tb);
    vec3_add(&(ray->orig), &tb, &res);
    vec3_copy_into(&res, result); // sets the result, sort of like returning
}