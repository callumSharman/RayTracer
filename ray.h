#ifndef _RAY_H_
#define _RAY_H_

#include "vec3.h"

typedef struct ray ray_t;
typedef struct spheres spheres_t;

struct ray {
    point3_t orig; // origin
    vec3_t dir; // direction
};

/* initialise ray instance. Takes origin and direction*/
ray_t ray_init(point3_t origin, vec3_t direction);

/* finds the point on the given ray at t */
point3_t ray_point_at(ray_t r, double t);

/* takes a ray and list of spheres in the world returns, the colour of a ray */
colour_t ray_colour(ray_t ray, spheres_t sphere_list);

#endif