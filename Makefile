CLFAGS = -Wall -g
CC= gcc


imageGenerator: main.o ppmCreator.o utils.o vec3.o
	gcc $(CFLAGS) -o imageGenerator main.o ppmCreator.o utils.o vec3.o

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o

ppmCreator.o: ppmCreator.c
	gcc $(CFLAGS) -c ppmCreator.c -o ppmCreator.o

utils.o: utils.c
	gcc $(CFLAGS) -c utils.c -o utils.o

vec3.o: vec3.c
	gcc $(CFLAGS) -c vec3.c -o vec3.o

run:
	make imageGenerator

clean:
	rm -f *.o 
	rm image.ppm
	rm imageGenerator