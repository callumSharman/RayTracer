#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include <stdio.h>

#define SAMPLES_PER_PIXEL 100
#define MAX_DEPTH 50
#define VFOV 20
#define LOOKFROM vec3_init(-2,2,1)
#define LOOKAT vec3_init(0,0,-1)
#define VUP vec3_init(0,1,0)



typedef struct camera camera_t;

struct camera {
    double aspect_ratio; // ratio of image width over height
    int img_width; // rendered image width
    int img_height; // rendered image height
    point3_t center; // camera center
    point3_t pixel00_loc; // location of pixel (0,0)
    vec3_t pixel_delta_u; // offset of pixel to the right
    vec3_t pixel_delta_v; // offset of pixel below
    int samples_per_pixel; // number of random samples for each pixel
    int max_depth; // max number of ray bounces

    double vfov; // vertical field of view
    point3_t lookfrom; // point the camera is looking from
    point3_t lookat; // point the camera is looking to
    vec3_t vup; // camera relative up direction

    /* camera frame basis vectors */
    vec3_t u;
    vec3_t v;
    vec3_t w;
};

/* initialise camera instance */
camera_t camera_init(double aspect_ratio, int img_width);

/* renders the objects given to the file given */
void render(FILE* img, camera_t camera, spheres_t sphere_list);

/* takes a ray and list of spheres in the world, returns the colour of a ray,
   depth is how many bounces left you wish to go */
colour_t ray_colour(ray_t ray, spheres_t sphere_list, int depth);

/* get a randomly sampled camera ray for the pixel at (i,j) */
ray_t get_ray(int i, int j, camera_t cam);

/* returns a random point in the square surrounding a pixel at the origin */
vec3_t pixel_sample_square(camera_t cam);

#endif