acquisition: main.o gpiolib.o
	gcc main.o gpiolib.o -lm -o acquisition

main.o: main.c
	gcc -c -I main.c

gpiolib.o: gpiolib.c
	gcc -c -I gpiolib.c
