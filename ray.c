#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "interval.h"


/* initialise ray instance. Takes origin and direction */
ray_t ray_init(point3_t origin, vec3_t direction){
    ray_t r;
    r.orig = origin; r.dir = direction;
    return r;
}


/* finds the point on the given ray at t */
point3_t ray_point_at(ray_t r, double t){
    // P(t) = A + tb (A is orign, b is direction)
    return(vec3_add(r.orig, vec3_multi(r.dir, t)));
        
}