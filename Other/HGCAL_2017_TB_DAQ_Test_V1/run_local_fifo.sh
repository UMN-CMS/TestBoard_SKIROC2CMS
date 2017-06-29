#!/bin/bash -v

mv ejf_local_fifo.o ejf_local_fifo.old
mv spi_hexaboard.o spi_hexaboard.old
mv spi_fast_read.o spi_fast_read.old
mv ejf_local_fifo ejf_local_fifo.bak

gcc -std=c11 -O -c spi_hexaboard.c -l bcm2835
gcc -std=c11 -O -c spi_fast_read.c
gcc -std=c11 -O -c ejf_local_fifo.c 
gcc ejf_local_fifo.o spi_hexaboard.o spi_fast_read.o -l bcm2835 -o ejf_local_fifo

sudo ./ejf_local_fifo
