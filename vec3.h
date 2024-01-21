#ifndef _VEC3_H_
#define _VEC3_H_


typedef struct vec3 vec3_t;
// point3 is just an alias for vec3, but useful for geometric clarity in the code.
typedef struct vec3 point3_t;

struct vec3 {
    double x;
    double y;
    double z;
};

/* initialise vec3 instance. Takes x, y, z and a pointer to your vector */
void init_vec3(vec3_t* v, double x, double y, double z);


void print_vec3(vec3_t* v);

#endif