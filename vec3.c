#include <stdio.h>
#include <math.h>

#include "vec3.h"


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

/* calculates and returns the unit vector of the given vector */
vec3_t vec3_unit_vec(vec3_t v){
    return vec3_divide(v, vec3_mag(v));
}

/* calculates and returns the dot product of the given vectors */
double vec3_dot(vec3_t v1, vec3_t v2){
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

/* prints the vector to console in easily readable format */
void vec3_print(vec3_t v){
    printf("Vector3(%f,%f,%f)\n", v.x, v.y, v.z);
}