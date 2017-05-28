//--------------------------------------------------------------------
// COMPILE: 
// gcc -g pwr_cycle.c -o pwr_cycle -l bcm2835 -Wall -std=c11
//--------------------------------------------------------------------
// USAGE: 
// sudo ./pwr_cycle 0
// sudo ./pwr_cycle 1
// sudo ./pwr_cycle 2
// sudo ./pwr_cycle 3
// sudo ./pwr_cycle 4
//--------------------------------------------------------------------
//	Power cycle the FPGAs
//--------------------------------------------------------------------

#include <bcm2835.h>
#include "BoardInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void die(const char *s);
void init_SPI();
void end_SPI();

int main (int argc, char *argv[])
{
	if (argc != 2) {fprintf(stderr,"ERR: usage.\n"); return(-1);}
	int My_ORM;
	My_ORM = atoi(argv[1]);

	// Setting up SPI
	init_SPI();
	
	char PAGE[1];
	char GPIO_PIN;
	     if (My_ORM == 0) GPIO_PIN = 0;
	else if (My_ORM == 1) GPIO_PIN = 1;
	else if (My_ORM == 2) GPIO_PIN = 2;
	else if (My_ORM == 3) GPIO_PIN = 3;
	else if (My_ORM == 4) GPIO_PIN = 4;

	// Time to power cycle the FPGA
	printf("Power cycling ORM%d...",My_ORM); fflush(stdout);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);	// CS0

	PAGE[0] = 0xF;
	bcm2835_spi_writenb(PAGE, sizeof(PAGE));
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);	// CS1
	
	// Clearing Pin
	char PIN_SELECT = 0xFF ^ (1 << GPIO_PIN);
	char PIN_as_output[] = {0x40, 0x01, PIN_SELECT};	// Want PIN to be an output
	bcm2835_spi_writenb(PIN_as_output, sizeof(PIN_as_output)+1);
	char PIN_low[] = {0x40, 0x13, PIN_SELECT};	// Set PIN to output low
	bcm2835_spi_writenb(PIN_low, sizeof(PIN_low)+1);
	sleep(5);						// Wait!
	char PIN_as_input[] = {0x40, 0x01, 0xFF};		// Set PIN as input again
	bcm2835_spi_writenb(PIN_as_input, sizeof(PIN_as_input)+1);


       //int status, hexbd;
       //hexbd = My_ORM * 2;
       //status = spi_verify_hexbd_communication(hexbd);
       //hexbd = (My_ORM * 2) + 1;
       //status = spi_verify_hexbd_communication(hexbd);

	printf(" Finished\n");

	// Closing time
	end_SPI();
	return 0;
}



void die(const char *s)
{
	printf("\n");
	printf(s);
	printf("\n");
	end_SPI();
	exit(1);
}



void init_SPI()
{
	if(!bcm2835_init())
	{
		die("bcm2825_init failed. You most likely are not running as root.");
	}

	if(!bcm2835_spi_begin())
	{
		die("bcm2825_spi_begin failed. You most likely are not running as root.");
	}

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);	// 1.5625 MHz
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);			// Chip-Select 0
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);	// Value of CS when active


}



void end_SPI()
{
	bcm2835_spi_end();
	bcm2835_close();
}
