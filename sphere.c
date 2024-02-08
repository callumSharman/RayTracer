#include <stdio.h>
#include <math.h>
#include "sphere.h"
#include "vec3.h"
#include "ray.h"

/* returns whether a particular ray hits the given sphere, within the given t values
   modifies the given hit record */
int sphere_hit(ray_t r, sphere_t sphere, double rayt_min, double rayt_max, hit_record_t* hr){
    // skipped step 6.2 to simplify this code
    // using the quadratic formula find the discriminant to see if intersection
    
    double a = vec3_dot(r.dir, r.dir);
    double b = 2 * vec3_dot(r.dir, vec3_sub(r.orig, sphere.center));
    double c = vec3_dot(vec3_sub(r.orig, sphere.center), vec3_sub(r.orig, sphere.center)) - sphere.radius*sphere.radius;
    double discriminant = (b*b) - (4*a*c);
    double sqrt_discrim = sqrt(discriminant);

    // find the nearest root within the acceptable range
    double half_b = vec3_dot(vec3_sub(r.orig, sphere.center), r.dir);

    // this is the closest, if this is not within range, check the other
    double root = ((half_b * -1) - sqrt_discrim) / a;
    if(root <= rayt_min || rayt_max <= root) {
        double root = ((half_b * -1) + sqrt_discrim) / a;
        if(root <= rayt_min || rayt_max <= root){
            return -1;
        }
    }

    hr->t = root;
    hr->p = ray_point_at(r, hr->t);
    vec3_t outward_normal = vec3_divide(vec3_sub(hr->p, sphere.center), sphere.radius);
    sphere_set_face_normal(r, &outward_normal, hr);
    return 1;
}

/* takes the outward normal of the circle, the ray and the hit_record
   corrects the normal and front_face values */
void sphere_set_face_normal(ray_t r, vec3_t* outward_normal, hit_record_t* hr){
        
    hr->front_face = vec3_dot(r.dir, *outward_normal) < 0;

    // if the hit record intersected on the front face then the outward normal is fine
    if(hr->front_face) hr->normal = *outward_normal;
    else hr->normal = vec3_multi(*outward_normal, -1);

}