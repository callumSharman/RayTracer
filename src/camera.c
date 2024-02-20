#include <stdio.h>
#include <math.h>
#include "camera.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "utils.h"
#include "materials.h"


/* initialise camera instance */
camera_t camera_init(double aspect_ratio, int img_width){
    camera_t cam;

    cam.defocus_angle = DEFOCUS_ANGLE;
    cam.focus_dist = FOCUS_DIST;

    cam.aspect_ratio = aspect_ratio;
    cam.img_width = img_width;
    cam.img_height = (img_width / (double) (aspect_ratio));
    cam.img_height = (cam.img_height < 1) ? 1 : cam.img_height; // must be at least 1 pixel tall
    
    cam.lookfrom = LOOKFROM;
    cam.lookat = LOOKAT;
    cam.vup = VUP;

    cam.center = cam.lookfrom;

    cam.vfov = VFOV;
    double theta = degrees_to_radians(cam.vfov);
    double h = tan(theta/2);
    double viewport_height = 2 * h * cam.focus_dist;
    double viewport_width = viewport_height * (cam.img_width/(double)cam.img_height);

    cam.w = vec3_unit_vec(vec3_sub(cam.lookfrom,cam.lookat));
    cam.u = vec3_unit_vec(vec3_cross(cam.vup, cam.w));
    cam.v = vec3_cross(cam.w, cam.u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3_t viewport_u = vec3_multi(cam.u, viewport_width);
    vec3_t viewport_v = vec3_multi(vec3_multi(cam.v,-1), viewport_height);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    cam.pixel_delta_u = vec3_divide(viewport_u, cam.img_width);
    cam.pixel_delta_v = vec3_divide(viewport_v, cam.img_height);

    // Calculate the location of the upper left pixel.
    /* viewport_upper_left = camera_center 
                            - vec3(0, 0, focal_length)
                            - viewport_u/2
                            - viewport_v/2 */
    vec3_t viewport_upper_left = vec3_sub(vec3_sub(vec3_sub(cam.center, 
                                    vec3_multi(cam.w, cam.focus_dist)), 
                                    vec3_divide(viewport_u,2)),
                                    vec3_divide(viewport_v,2));

    /* pixel00_loc = viewport_upper_left + 
                            (0.5 * (pixel_delta_u + pixel_delta_v)) */
    // im fairly certain this is the center of the top left pixel
    cam.pixel00_loc = vec3_add(viewport_upper_left, 
                                vec3_multi(vec3_add(cam.pixel_delta_u, cam.pixel_delta_v), 0.5));

    cam.samples_per_pixel = SAMPLES_PER_PIXEL;
    cam.max_depth = MAX_DEPTH;

    double defocus_radius = cam.focus_dist * tan(degrees_to_radians(cam.defocus_angle/2));
    cam.defocus_disk_u = vec3_multi(cam.u, defocus_radius);
    cam.defocus_disk_v = vec3_multi(cam.v,defocus_radius);
                                
    return cam;
}

/* renders the objects given to the file given */
void render(FILE* img, camera_t camera, spheres_t sphere_list){

    fprintf(img, "P3\n%d %d\n255\n", camera.img_width, camera.img_height);

    for(int i = 0; i < camera.img_height; i ++) {
        for(int j = 0; j < camera.img_width; ++j) {
            colour_t pixel_colour = vec3_init(0,0,0);

            // run sampling for antialiasing
            for(int sample = 0; sample < camera.samples_per_pixel; ++sample){
                ray_t r = get_ray(j, i, camera);
                pixel_colour = vec3_add(pixel_colour, 
                                    ray_colour(r, sphere_list, camera.max_depth));
            }

            write_colour(img, pixel_colour, camera.samples_per_pixel);

        }

        printProgress(i, camera.img_height);
    }

}

/* takes a ray and list of spheres in the world, returns the colour of a ray,
   depth is how many bounces left you wish to go */
colour_t ray_colour(ray_t ray, spheres_t sphere_list, int depth){

    /*========================SPHERES========================*/
    hit_record_t hr;

    // max depth reached means full black (in complete shadow)
    if(depth <= 0) return vec3_init(0,0,0);

    if(spheres_hit(ray, sphere_list, interval_init(0.001, INFINITY), &hr)){
        ray_t scattered;
        vec3_t attenuation;

        if(hr.material.scatter_func(ray, &hr, &attenuation, &scattered)){
            return(vec3_element_wise_multi(attenuation, ray_colour(scattered ,sphere_list, depth-1)));
        }
        return vec3_init(0,0,0);



        // standard diffuse illumination
        //vec3_t direction = vec3_rand_on_hemisphere(hr.normal);

        // lambertian illumination
            // lamb. gives rays that more often point towards the normal, 
            // the standard is more evenly spread
        // vec3_t direction = vec3_add(hr.normal, vec3_rand_unit());

        // return(vec3_multi(ray_colour(ray_init(hr.p, direction) ,sphere_list, depth-1), 0.5));
    }

    /*========================BACKGROUND========================*/

    // find the unit vector of the direction
    vec3_t unit_dir = vec3_unit_vec(ray.dir);

    // set start and end colours of the gradient
    colour_t start_col = vec3_init(1.0, 1.0, 1.0);
    colour_t end_col = vec3_init(0.5, 0.7, 1.0);
    
    // move based on vertically, based on y value of position. Set between 0 and 1
    double a = 0.5 * (unit_dir.y + 1.0);

    colour_t blended_value = vec3_add(vec3_multi(start_col, (1-a)), vec3_multi(end_col, a));
    return blended_value;
}

/* get a randomly sampled camera ray for the pixel at (i,j), 
   originating from the camera defocus disk */
ray_t get_ray(int i, int j, camera_t cam){
    vec3_t pixel_center = vec3_add(cam.pixel00_loc, 
                          vec3_add((vec3_multi(cam.pixel_delta_u, i)), 
                                   (vec3_multi(cam.pixel_delta_v, j))));
    vec3_t pixel_sample = vec3_add(pixel_center, pixel_sample_square(cam));

    vec3_t ray_origin = (cam.defocus_angle <= 0) ? cam.center : defocus_disk_sample(cam);
    vec3_t ray_dir = vec3_sub(pixel_sample, ray_origin);
    return ray_init(ray_origin, ray_dir);
}

/* returns a random point in the square surrounding a pixel at the origin */
vec3_t pixel_sample_square(camera_t cam){
    double px = -0.5 + rand_double();
    double py = -0.5 + rand_double();
    return(vec3_add((vec3_multi(cam.pixel_delta_u, px)), 
                    (vec3_multi(cam.pixel_delta_v, py))));
    
}

/* returns a random point in the camera defocus disk */
point3_t defocus_disk_sample(camera_t cam){
    point3_t p = vec3_rand_in_unit_disk();
    return(vec3_add(vec3_add(cam.center, 
                    vec3_multi(cam.defocus_disk_u, p.x)),
                    vec3_multi(cam.defocus_disk_v, p.y)));
}