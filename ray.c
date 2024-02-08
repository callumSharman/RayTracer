#include <stdio.h>
#include <math.h>
#include "utils.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"


/* initialise ray instance. Takes origin and direction*/
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

/* takes a ray and list of spheres in the world, returns the colour of a ray */
colour_t ray_colour(ray_t ray, spheres_t sphere_list){

    /*========================SPHERES========================*/
    hit_record_t hr;
    if(spheres_hit(ray, sphere_list, 0, INFINITY, &hr)){
        return(vec3_multi( vec3_add(hr.normal, vec3_init(1,1,1)) , 0.5));
    }

    /*========================GROUND========================*/

    // find the unit vector of the direction
    vec3_t unit_dir = vec3_unit_vec(ray.dir);

    // set start and end colours of the gradient
    colour_t start_col = vec3_init(1.0, 1.0, 1.0);
    colour_t end_col = vec3_init(0.5, 0.7, 1.0);
    
    // move based on vertically, based on y value of position. Set between 0 and 1
    double a = 0.5 * (unit_dir.y + 1.0);

    colour_t blended_value = vec3_add(vec3_multi(start_col, (1-a)), vec3_multi(end_col, a));
    return blended_value;
}