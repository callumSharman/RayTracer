#include <stdio.h>
#include <math.h>
#include "sphere.h"
#include "vec3.h"
#include "ray.h"

/* initialise sphere instance. Takes the center and radius*/
sphere_t sphere_init(point3_t center, double radius){
    sphere_t sphere;
    sphere.center = center;
    sphere.radius = radius; 
    return sphere;
}

/* initialise sphere list instance */
spheres_t spheres_init(){
    spheres_t spheres;
    spheres.num_spheres = 0; 
    return spheres;
}

/* returns whether a particular ray hits the given sphere, within the given t values
   modifies the given hit record */
int sphere_hit(ray_t r, sphere_t sphere, double rayt_min, double rayt_max, hit_record_t* hr){
    // skipped step 6.2 to simplify this code
    // using the quadratic formula find the discriminant to see if intersection
    
    double a = vec3_dot(r.dir, r.dir);
    double b = 2 * vec3_dot(r.dir, vec3_sub(r.orig, sphere.center));
    double c = vec3_dot(vec3_sub(r.orig, sphere.center), vec3_sub(r.orig, sphere.center)) - sphere.radius*sphere.radius;
    double discriminant = (b*b) - (4*a*c);
    if(discriminant < 0) return 0;
    double sqrt_discrim = sqrt(discriminant);

    // find the nearest root within the acceptable range
    double half_b = vec3_dot(vec3_sub(r.orig, sphere.center), r.dir);

    // this is the closest, if this is not within range, check the other
    double root = ((half_b * -1) - sqrt_discrim) / a;
    if(root <= rayt_min || rayt_max <= root) {
        root = ((half_b * -1) + sqrt_discrim) / a;
        if(root <= rayt_min || rayt_max <= root){
            return 0;
        }
    }

    hr->t = root;
    hr->p = ray_point_at(r, hr->t);
    vec3_t outward_normal = vec3_divide(vec3_sub(hr->p, sphere.center), sphere.radius);
    sphere_set_face_normal(r, &outward_normal, hr);
    return 1;
}

/* returns whether a particular ray hits any of the given spheres, within the given t values
   modifies the given hit record to be the closest sphere hit */
int spheres_hit(ray_t r, spheres_t sphere_list, double rayt_min, double rayt_max, hit_record_t* hr){
    hit_record_t temp_hr;
    int hit_anything = 0;
    double closest_so_far = rayt_max;
    for(int i = 0; i < sphere_list.num_spheres; i ++){
        // if there is a closer hit with the next sphere then update it
        if(sphere_hit(r, sphere_list.spheres[i], rayt_min, closest_so_far, &temp_hr)){
            hit_anything = 1;
            closest_so_far = temp_hr.t;
            copy_hit_record(hr, &temp_hr); // this line may cause errors
        }
    }

    return hit_anything;
}

/* copies the information from hr2 to hr1 */
void copy_hit_record(hit_record_t* hr1, hit_record_t* hr2){
    hr1->p = hr2->p; 
    hr1->normal = hr2->normal;
    hr1->t = hr2->t;
    hr1->front_face = hr2->front_face;
}


/* takes the outward normal of the circle, the ray and the hit_record
   corrects the normal and front_face values */
void sphere_set_face_normal(ray_t r, vec3_t* outward_normal, hit_record_t* hr){
        
    hr->front_face = vec3_dot(r.dir, *outward_normal) < 0;

    //hr->normal = hr->front_face ? *outward_normal : vec3_multi(*outward_normal, -1);

    // if the hit record intersected on the front face then the outward normal is fine
    if(hr->front_face) hr->normal = *outward_normal;
    else hr->normal = vec3_multi(*outward_normal, -1);

}