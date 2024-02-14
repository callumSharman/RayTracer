# RAY TRACER
what is it

## Operation
### Execution
Use the command `make run` to complie all necessary files and execute. Outputs the result into image.ppm in the root folder.

Use the command `make clean` to delete all executeables, object files and the image named "image.ppm" in the root from previous execution.

### Camera/Image manipulation
(Make sure when changing camera constants to execute `make clean` before `make run`)

The following is a list of modifiable constants within the file *camera.h*

* Samples per pixel
* Max depth
* Vfov
* Look from
* Look at
* Vup
* Defocus angle
* Focus distance

Within *main.c* the image width can be modified.



### Adding objects

## Examples
<p align="center">
  <img src="images/pngs/final_1_highres.png" width="400">
</p>

### diffuse surfaces
<p align="center">
  <img src="images/pngs/diffuse_4_lam.png" width="400">
  <img src="images/pngs/diffuse_5_lam_colour.png" width="400">
</p>

### metal surfaces
<p align="center">
  <img src="images/pngs/metal_2.png" width="400">
  <img src="images/pngs/metal_3_fuzzed.png" width="400">
</p>

### glass surfaces
<p align="center">
  <img src="images/pngs/camera_angle_1.png" width="400">
</p>


## Retrospective
what did i learn here

not the right language for this. for example problems with materials
the material struct has values in there that arent relevant to all materials

i need to learn about headers, how to prevent circular dependencies needing
forward declarations