#include <stdio.h>


/*
int main() {

   // image
   FILE *img = fopen("image.ppm", "w");
   int img_width = 256;
   int img_height = 256;

   // render
   fprintf(img, "P3\n%d %d\n255\n", img_width, img_height);

   for (int i = 0; i < img_height; i++) {
      for (int j = 0; j < img_width; j++) {
         double r = (double)(j) / (img_width-1);
         double g = (double)(i) / (img_height-1);
         double b = 0;

         int ir = (int)(255.999 * r);
         int ig = (int)(255.999 * g);
         int ib = (int)(255.999 * b);

         fprintf(img, "%d %d %d\n", ir, ig, ib);
      }
   }


   fclose(img);
   return 0;
}*/