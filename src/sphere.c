#include <stdio.h>
#include <math.h>
#include "sphere.h"
#include "vec3.h"
#include "ray.h"
#include "interval.h"
#include "utils.h"
#include "materials.h"

/* initialise sphere instance. Takes the center and radius*/
sphere_t sphere_init(point3_t center, double radius, material_t material){
    sphere_t sphere;
    sphere.center = center;
    sphere.radius = radius; 
    sphere.material = material;
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
int sphere_hit(ray_t r, sphere_t sphere, interval_t rayt, hit_record_t* hr){

    // using the quadratic formula find the discriminant to see if intersection
    vec3_t oc = vec3_sub(r.orig, sphere.center);
    double a = vec3_length_squared(r.dir);
    double half_b = vec3_dot(oc, r.dir);
    double c = vec3_length_squared(oc) - (sphere.radius*sphere.radius);

    double discriminant = (half_b * half_b) - (a*c);
    if(discriminant < 0) return 0;
    double sqrt_discrim = sqrt(discriminant);
    // this is the closest, if this is not within range, check the other
    double root = ((half_b * -1) - sqrt_discrim) / a;
    if(!interval_surrounds(rayt, root)) {
        root = ((half_b * -1) + sqrt_discrim) / a;
        if(!interval_surrounds(rayt, root)){
            return 0;
        }
    }

    hr->t = root;
    hr->p = ray_point_at(r, hr->t);
    vec3_t outward_normal = vec3_divide(vec3_sub(hr->p, sphere.center), sphere.radius);
    sphere_set_face_normal(r, &outward_normal, hr);
    hr->material = sphere.material;

    return 1;
}

/* returns whether a particular ray hits any of the given spheres, within the given t values
   modifies the given hit record to be the closest sphere hit */
int spheres_hit(ray_t r, spheres_t sphere_list, interval_t rayt, hit_record_t* hr){

    hit_record_t temp_hr;
    int hit_anything = 0;
    double closest_so_far = rayt.max;
    for(int i = 0; i < sphere_list.num_spheres; i ++){
        // if there is a closer hit with the next sphere then update it
        if(sphere_hit(r, sphere_list.spheres[i], interval_init(rayt.min, closest_so_far), &temp_hr)){
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
    copy_material(&(hr1->material), &(hr2->material));
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

/* prints the sphere to console in easily readable format */
void sphere_print(sphere_t s){
    printf("Center: "); 
    vec3_print(s.center);
    printf("Radius: %f\n", s.radius);
}
