#include "vec3.h"


/* initialise vec3 instance. Takes x, y, z and a pointer to your vector */
void init_vec3(vec3_t* v, double x, double y, double z){
    v->x = x;
    v->y = y;
    v->z = z;

    return;
}

//magnitude

//add 

//display
void print_vec3(vec3_t* v){
    printf("Vector3(%f,%f,%f)\n", v->x, v->y, v->z);
}