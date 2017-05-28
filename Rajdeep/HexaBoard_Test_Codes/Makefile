acquisition: main.o gpiolib.o
	gcc main.o gpiolib.o bcm2835.o -lm -o acquisition

main.o: main.c
	gcc -c -I ./RPi_software/bcm2835-1.52/src ./RPi_software/bcm2835-1.52/src/bcm2835.c main.c

gpiolib.o: gpiolib.c
	gcc -c -I ./RPi_software/bcm2835-1.52/src ./RPi_software/bcm2835-1.52/src/bcm2835.c gpiolib.c
