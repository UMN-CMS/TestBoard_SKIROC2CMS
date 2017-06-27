//---------------------------------------------------------------------
// COMPILE:
// gcc wiggle_mode.c -o wiggle_mode -l bcm2835 -Wall -std=c11
//---------------------------------------------------------------------
// USAGE:
// 	sudo ./wiggle_mode
//---------------------------------------------------------------------
//	Flips MODE every half second
//---------------------------------------------------------------------

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define MODE RPI_GPIO_P1_07 // GPIO 4 or physical pin 7


void init_SPI();
void end_SPI();


int main() {

	// Setting up SPI
	init_SPI();

	bcm2835_gpio_fsel(MODE, BCM2835_GPIO_FSEL_OUTP);

	int i = 0;
	while(1) {

		// make MODE low or high
		if(i%2) {
			bcm2835_gpio_write(MODE, HIGH);
			//printf("MODE Status: 1\n");
		}
		else {
			bcm2835_gpio_write(MODE, LOW);
			//printf("MODE Status: 0\n");
		}

		sleep(0.5);
		i++;
	}

	end_SPI();
	return 0;
}



void init_SPI() {
	if(!bcm2835_init()) {
		printf("bcm2825_init failed. You most likely are not running as root.\n");
		exit(1);
	}

	if(!bcm2835_spi_begin()) {
		printf("bcm2825_spi_begin failed. You most likely are not running as root.\n");
		exit(1);
	}

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);	// 1.5625 MHz
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);			// Chip-Select 0
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);	// Value of CS when active
}



void end_SPI() {
	bcm2835_spi_end();
	bcm2835_close();
}
