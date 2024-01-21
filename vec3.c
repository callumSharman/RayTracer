#include <stdio.h>
#include <math.h>

#include "vec3.h"


/* initialise vec3 instance. Takes x, y, z and a pointer to your vector */
void vec3_init(vec3_t* v, double x, double y, double z){
    v->x = x;
    v->y = y;
    v->z = z;
}

/* returns the magnitude of given vec3 */
double vec3_mag(vec3_t* v){

    return sqrt((v->x * v->x) + 
                (v->y * v->y) + 
                (v->z * v->z));
}

/* adds 2 vectors, puts the result into 'result' */ 
void vec3_add(vec3_t* v1, vec3_t* v2, vec3_t* result){
    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;
}

/* prints the vector to console in easily readable format */
void vec3_print(vec3_t* v){
    printf("Vector3(%f,%f,%f)\n", v->x, v->y, v->z);
}