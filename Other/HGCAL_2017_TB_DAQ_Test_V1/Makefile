Test_DAQ: Test_Pi_Configuration.o spi_hexaboard.o spi_clear_busy.o spi_fast_read.o
	gcc Test_Pi_Configuration.o spi_hexaboard.o spi_clear_busy.o spi_fast_read.o -l bcm2835 -o Test_DAQ

Test_Pi_Configuration.o: Test_Pi_Configuration.c
	gcc -c Test_Pi_Configuration.c -Wall -std=c11

spi_fast_read.o: spi_fast_read.c
	gcc -c spi_fast_read.c -Wall -std=c11

spi_hexaboard.o: spi_hexaboard.c
	gcc -c spi_hexaboard.c -l bcm2835 -Wall -std=c11

spi_clear_busy.o: spi_clear_busy.c
	gcc -c spi_clear_busy.c -l bcm2835 -Wall -std=c11
