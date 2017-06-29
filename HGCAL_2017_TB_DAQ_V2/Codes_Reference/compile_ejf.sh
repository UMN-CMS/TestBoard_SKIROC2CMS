#!/bin/bash
set verbose
	

gcc -std=c11 -O -c spi_hexaboard.c -l bcm2835
gcc -std=c11 -O -c spi_clear_busy.c -l bcm2835
gcc -std=c11 -O -c spi_fast_read.c
gcc -std=c11 -O -c Test_Pi_Configuration.c 
gcc -std=c11 -O -c Test_Pi_Pedestal.c
gcc -std=c11 -O -c Test_Pi_Pedestal_Combined.c

gcc Test_Pi_Configuration.o spi_hexaboard.o spi_clear_busy.o spi_fast_read.o -l bcm2835 -o Test_DAQ

gcc Test_Pi_Pedestal.o spi_hexaboard.o spi_clear_busy.o spi_fast_read.o -l bcm2835 -o Test_DAQ_Pedestal

gcc Test_Pi_Pedestal_Combined.o spi_hexaboard.o spi_clear_busy.o spi_fast_read.o -l bcm2835 -o Test_DAQ_Pedestal_Combined

gcc sleep.c -o take_a_nap.exe
