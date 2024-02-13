#include <stdio.h>
#include <math.h>

#include "vec3.h"
#include "utils.h"


/* initialise vec3 instance. Takes x, y, z doubles */
vec3_t vec3_init(double x, double y, double z){
    vec3_t v;
    v.x = x; v.y = y; v.z = z;
    return v;
}

/* returns the magnitude of given vec3 */
double vec3_mag(vec3_t v){

    return sqrt((v.x * v.x) + 
                (v.y * v.y) + 
                (v.z * v.z));
}

/* adds a vector and magnitude */ 
vec3_t vec3_add_mag(vec3_t v, double a){
    return vec3_init(v.x + a, v.y + a, v.z + a);
}

/* adds 2 vectors */ 
vec3_t vec3_add(vec3_t v1, vec3_t v2){
    return vec3_init(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

// /* subtracts a vector by a magnitude */ 
// vec3_t vec3_sub_mag(vec3_t v, double a){
//     return vec3_init(v.x - a, v.y - a, v.z - a);
// }

/* subtracts v2 from v1 */ 
vec3_t vec3_sub(vec3_t v1, vec3_t v2){
    return vec3_init(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

/* multiples a vec3 by the given magnitude */
vec3_t vec3_multi(vec3_t v, double a){
    return vec3_init(v.x * a, v.y * a, v.z * a);
}

/* divides a vec3 by the given magnitude */
vec3_t vec3_divide(vec3_t v, double a){
    return vec3_init(v.x / a, v.y / a, v.z / a);
}

/* multiplies the elements of the given vectors */
vec3_t vec3_element_wise_multi(vec3_t v1, vec3_t v2){
    return(vec3_init(v1.x * v2.x,
                     v1.y * v2.y,
                     v1.z * v2.z));
}

/* calculates and returns the unit vector of the given vector */
vec3_t vec3_unit_vec(vec3_t v){
    return vec3_divide(v, vec3_mag(v));
}

/* calculates and returns the dot product of the given vectors */
double vec3_dot(vec3_t v1, vec3_t v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

/* calculates and returns the cross product of the given vectors */
vec3_t vec3_cross(vec3_t u, vec3_t v){
    return(vec3_init((u.y * v.z) - (u.z * v.y),
                     (u.z * v.x) - (u.x * v.z),
                     (u.x * v.y) - (u.y * v.x)
    ));
}

/* calculates the length squared */
double vec3_length_squared(vec3_t v){
    return((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
}

/* prints the vector to console in easily readable format */
void vec3_print(vec3_t v){
    printf("Vector3(%f,%f,%f)\n", v.x, v.y, v.z);
}

/* returns a random vector with values in [0,1) */
vec3_t vec3_random(){
    return(vec3_init(rand_double(), 
                     rand_double(), 
                     rand_double()));
}

/* returns a random vector with values in [min,max) */
vec3_t vec3_random_min_max(double min, double max){
    return(vec3_init(rand_double_min_max(min, max),
                     rand_double_min_max(min, max),
                     rand_double_min_max(min, max)));
}

/* generates random vec3 in the unit sphere */
vec3_t vec3_rand_in_unit_sphere(){
    // generate using rejection method. 
    // pick a random point in the unit cube
    // reject the point if it is outside the sphere
    while(1){
        vec3_t point = vec3_random_min_max(-1,1);
        if(vec3_length_squared(point) < 1){
            return point;
        }
    }
}

/* generates a random unit vector on the unit sphere */
vec3_t vec3_rand_unit(){
    return vec3_unit_vec(vec3_rand_in_unit_sphere());
}

/* generates a random vec3 on the same hemisphere as the given normal */
vec3_t vec3_rand_on_hemisphere(vec3_t normal){
    vec3_t vec_on_sphere = vec3_rand_unit();

    // positive dot product indicates same hemisphere
    if(vec3_dot(vec_on_sphere, normal) > 0){
        return vec_on_sphere;
    } else {
        return vec3_multi(vec_on_sphere, -1);
    }
}

/* returns true if the vector is close to zero in all dimensions */
int near_zero(vec3_t v){
    double s = 1e-8;
    return((fabs(v.x) < s) && 
           (fabs(v.y) < s) && 
           (fabs(v.z) < s)); 
}

/* returns the vector of a vector perfectly reflected off of a surface with normal n */
vec3_t vec3_reflect(vec3_t v, vec3_t n){
    return(vec3_sub(v, vec3_multi(vec3_multi(n, 2), vec3_dot(v,n))));
}

/* returns the vector of a vector refracted through a surface with normal n*/
vec3_t vec3_refract(vec3_t v, vec3_t n, double etai_over_etat){
    double cos_theta = fmin(vec3_dot(vec3_multi(v,-1), n), 
                            1.0);
    vec3_t r_out_perp = vec3_multi(vec3_add(v, vec3_multi(n, cos_theta)), 
                        etai_over_etat); 
    vec3_t r_out_parallel = vec3_multi(n,
                        (-1 * (sqrt(fabs(1.0 - vec3_length_squared(r_out_perp))))));
    return(vec3_add(r_out_perp, r_out_parallel));
}