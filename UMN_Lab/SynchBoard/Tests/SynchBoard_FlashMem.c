//
//	Synch Board FLASH Memory Test
//

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>


#define FPGA_PAGE 0x3


void die(const char *s);
void init_SPI();
void end_SPI();


int main()
{
	// Setting up SPI
	init_SPI();
	printf("FLASH MEMORY TEST\n\n");

	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);	// CS0
	char PAGE[] = {FPGA_PAGE};
	bcm2835_spi_writenb(PAGE,1);			// Sending PAGE FPGA_PAGE
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);	// CS1

	char RDID[] = {0x9E, 0x0, 0x0, 0x0};		// RDID command w/ 3 zero bytes
	char data[sizeof(RDID)];
	bcm2835_spi_transfernb(RDID, data, sizeof(RDID));// Send RDID and read back into data

	printf("%02x %02x %02x\n\n", data[1], data[2], data[3]);

	// Close SPI
	end_SPI();
	return 0;
}



void die(const char *s)
{
	printf(s);
	exit(1);
}



void init_SPI()
{
	if(!bcm2835_init())
	{
		die("bcm2825_init failed. You most likely are not running as root.\n");
	}

	if(!bcm2835_spi_begin())
	{
		die("bcm2825_spi_begin failed. You most likely are not running as root.\n");
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
