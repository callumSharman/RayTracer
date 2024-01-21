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

/* initialise vec3 instance. Takes x, y, z and a pointer to vector */
void vec3_init(vec3_t* v, double x, double y, double z);

/* returns the magnitude of given vec3 */
double vec3_mag(vec3_t* v);

/* adds 2 vectors, puts the result into 'result' */ 
void vec3_add(vec3_t* v1, vec3_t* v2, vec3_t* result);

/* multiples a vec3 by the given magnitude */
void vec3_multiply(vec3_t* v, double x, vec3_t* result);

/* copies v1 into v2 */
void vec3_copy_into(vec3_t* v1, vec3_t* v2);

/* prints the vector to console in easily readable format */
void vec3_print(vec3_t* v); 

#endif