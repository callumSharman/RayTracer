CFLAGS = -Wall -g -lm
CC= gcc


imgGenerator: main.o utils.o vec3.o ray.o sphere.o interval.o
	$(CC) -o imgGenerator main.o utils.o vec3.o ray.o sphere.o interval.o $(CFLAGS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

utils.o: utils.c
	$(CC) -c utils.c -o utils.o $(CFLAGS)

vec3.o: vec3.c
	$(CC) -c vec3.c -o vec3.o $(CFLAGS)

ray.o: ray.c
	$(CC) -c ray.c -o ray.o $(CFLAGS)

sphere.o: sphere.c
	$(CC) -c sphere.c -o sphere.o $(CFLAGS)

interval.o: interval.c
	$(CC) -c interval.c -o interval.o $(CFLAGS)

run:
	make imgGenerator
	./imgGenerator

clean:
	rm -f *.o 
	rm imgGenerator
	rm image.ppm