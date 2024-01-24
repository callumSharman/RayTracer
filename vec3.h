#ifndef _VEC3_H_
#define _VEC3_H_


typedef struct vec3 vec3_t;
// point3 is just an alias for vec3, but useful for geometric clarity in the code.
typedef struct vec3 point3_t;

typedef struct vec3 colour_t;

struct vec3 {
    double x;
    double y;
    double z;
};

/* initialise vec3 instance. Takes x, y, z doubles */
vec3_t vec3_init(double x, double y, double z);

/* returns the magnitude of given vec3 */
double vec3_mag(vec3_t v);

/* adds a vector and magnitude */ 
vec3_t vec3_add_mag(vec3_t v, double a);

/* adds 2 vectors */ 
vec3_t vec3_add(vec3_t v1, vec3_t v2);

// /* subtracts a vector by a magnitude */ 
// vec3_t vec3_sub_mag(vec3_t v, double a);

/* subtracts v2 from v1 */ 
vec3_t vec3_sub(vec3_t v1, vec3_t v2);

/* multiples a vec3 by the given magnitude */
vec3_t vec3_multi(vec3_t v, double a);

/* divides a vec3 by the given magnitude */
vec3_t vec3_divide(vec3_t v, double a);

/* calculates and returns the unit vector of the given vector */
vec3_t vec3_unit_vec(vec3_t v);

/* calculates and returns the dot product of the given vectors */
double vec3_dot(vec3_t v1, vec3_t v2);

/* prints the vector to console in easily readable format */
void vec3_print(vec3_t v);

#endif