CFLAGS = -Wall -g -lm
CC= gcc
OJBS = main.o utils.o vec3.o ray.o sphere.o interval.o camera.o materials.o


imgGenerator: $(OJBS)
	$(CC) -o imgGenerator $(OJBS) $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

run:
	make imgGenerator
	./imgGenerator

clean:
	rm -f *.o 
	rm imgGenerator
	rm image.ppm