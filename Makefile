CFLAGS = -Wall -g -lm
CC= gcc
OJBS = src/main.o src/utils.o src/vec3.o src/ray.o src/sphere.o src/interval.o src/camera.o src/materials.o


imgGenerator: $(OJBS)
	$(CC) -o imgGenerator $(OJBS) $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

run:
	make imgGenerator
	./imgGenerator

clean:
	rm -f src/*.o 
	rm imgGenerator
	rm image.ppm