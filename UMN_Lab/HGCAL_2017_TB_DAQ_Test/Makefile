Test_DAQ: Test_Pi_Configuration.o spi_hexaboard.o
	gcc Test_Pi_Configuration.o spi_hexaboard.o -l bcm2835 -o Test_DAQ

Test_Pi_Configuration.o: Test_Pi_Configuration.c
	gcc -c Test_Pi_Configuration.c -Wall -std=c11

spi_hexaboard.o: spi_hexaboard.c
	gcc -c spi_hexaboard.c -l bcm2835 -Wall -std=c11

